//This is the Sine wave version. The mechanism makes the servos move fast in the middle and slow down at the edges. 
// The advantage is a more lifelike flapping motion that saves energy, though the flapping speed and power are weaker than the Triangle wave version.
// Max Flap Angle	flapAmplitude	40 - 85	Sets the peak travel (degrees) from the 90° center point. Values above 80 may strain mechanical linkages.
// Pulse Width	attach(pin, 500, 2500)	500 - 2500 us	Extends physical servo travel. Verify that your servos support 2500us to avoid motor burnout.
// Flapping Speed	speedFactor	50 - 150	Mapped to the Throttle channel. Defines the phase increment per loop (Sine/Triangle wave frequency).
// i also added a lot of comments to actually explain the code to someone who has no idea about how it works.


/*
 PETAL - BIONIC BUTTERFLY
 
 
 
  RC Channels:
   CH1 -> steering
   CH2 -> elevator
   CH3 -> flapping speed
   CH5 -> steering trim
   CH6 -> pitch trim / perch control 
   CH7 -> perch switch (or any other emote maybe, perch is isnpired by s-diy)
 */

#include <Servo.h>
#include <PPMReader.h>


// pin config

const byte PPM_PIN = 3;

const byte LEFT_SERVO_PIN  = 9;
const byte RIGHT_SERVO_PIN = 10;


// ppm config

const byte CHANNEL_COUNT = 7;

PPMReader ppm(PPM_PIN, CHANNEL_COUNT);


// servo config

Servo servoLeft;
Servo servoRight;

const int CENTER_ANGLE = 90;


// flapping conif

// maxm movement away from center basically,
// 65 means -
// Left:  90 + 65 = 155 degrees
// Right: 90 - 65 = 25 degrees
// the servos move opposite each other,
// this produces the wing-flapping motion, duhhh(?) :>

const int FLAP_AMPLITUDE = 65;

// max pitch trim correction
const int MAX_PITCH_TRIM = 20;

// flight state

float phase = 0.0;
float perchPhase = 0.0;

float currentOffset = 0.0;

bool isPerching = false;
bool wasFailsafe = true;


// servo position tracking

int lastLeftPosition  = CENTER_ANGLE;
int lastRightPosition = CENTER_ANGLE;


// ppm filtering

// stored channel values are like;
// Index 0 = CH1
// Index 1 = CH2
// and so onto
// Index 6 = CH7

int lastChannelValues[CHANNEL_COUNT] = {
  1500,
  1500,
  1500,
  1500,
  1500,
  1500,
  1500
};


// lets ignore the small ppm fluctuations.
const int PPM_DEADBAND = 3;

// serial debugging

unsigned long lastLogTime = 0;

const unsigned long LOG_INTERVAL = 1000;


// SETUP (IMP)

void setup() {

  Serial.begin(115200);

  // attaching servos
  // 500–2500 gives the servo library a wide usable pulse range

  servoLeft.attach(LEFT_SERVO_PIN, 500, 2500);
  servoRight.attach(RIGHT_SERVO_PIN, 500, 2500);


  // start both servos at their neutral position

  servoLeft.write(CENTER_ANGLE);
  servoRight.write(CENTER_ANGLE);

  lastLeftPosition  = CENTER_ANGLE;
  lastRightPosition = CENTER_ANGLE;


  Serial.println();
  Serial.println(" PETAL IS READY TO TOUCH THE SKIES ");
  Serial.println(" 2 Servo Sine-Wave Mode");
  Serial.println("System is ready.");
}

// reading filtered ppm channels

int readPPMFiltered(byte channelIndex) {

  // ppmreader channels are numbered starting from 1
  int rawValue = ppm.latestValidChannelValue(
    channelIndex + 1,
    1500
  );


  // Ignoring tiny fluctuations again

  if (abs(rawValue - lastChannelValues[channelIndex]) > PPM_DEADBAND) {
    lastChannelValues[channelIndex] = rawValue;
  }


  return lastChannelValues[channelIndex];
}

// MAIN LOOP (imp)

void loop() {

  // checking receiver connections

  unsigned long ch3Raw = ppm.latestValidChannelValue(3, 0);

  bool receiverConnected = (ch3Raw != 0);


  // FAILSAFE

  if (!receiverConnected) {

    processFailsafe();

  }


  // normal flight

  else {

    // reading rc channels

    int steering = readPPMFiltered(0);
    int elevator = readPPMFiltered(1);
    int throttle = readPPMFiltered(2);

    int steeringTrim = readPPMFiltered(4);
    int pitchControl = readPPMFiltered(5);
    int perchSwitch  = readPPMFiltered(6);

    // steering

    int steerValue = 0;

    if (abs(steering - 1500) > 10) {

      steerValue = map(
        steering,
        900,
        2100,
        -15,
        15
      );
    }


    // CH5 adds additional steering trim

    int finalSteer =
      steerValue +
      map(
        steeringTrim,
        1000,
        2000,
        -15,
        15
      );


    // elevator

    int elevatorOffset = 0;

    if (abs(elevator - 1500) > 10) {

      elevatorOffset = map(
        elevator,
        900,
        2100,
        -15,
        15
      );
    }


    // pitch trim

    int pitchTrim = map(
      pitchControl,
      1000,
      2000,
      -MAX_PITCH_TRIM,
      MAX_PITCH_TRIM
    );


    // perch mode (can be changes in future to add a different emotes or mocing state or something petal can do)

    if (throttle > 1100) {

      // any throttle means normal flight

      isPerching = false;

    }

    else if (
      perchSwitch > 1600 &&
      throttle < 1100
    ) {

      isPerching = true;
    }


    // switch fully off meanss normal mode

    if (perchSwitch < 1400) {

      isPerching = false;
    }


    // determining flight mode

    if (isPerching) {

      updatePerchMode(pitchControl);

    }

    else if (throttle < 1050) {

      updateGlideMode();

    }

    else {

      updateSineFlapping(throttle);
    }


    // calculating servo position

    int leftOutput =
      CENTER_ANGLE +
      (int)currentOffset +
      finalSteer +
      elevatorOffset +
      pitchTrim;


    int rightOutput =
      CENTER_ANGLE -
      (int)currentOffset +
      finalSteer -
      elevatorOffset -
      pitchTrim;


    // update servos

    updateServos(
      leftOutput,
      rightOutput
    );
  }

  // serial debug output


  if (millis() - lastLogTime > LOG_INTERVAL) {

    lastLogTime = millis();

    if (receiverConnected) {

      Serial.print("[CONNECTED] ");
      Serial.print("CH3: ");
      Serial.println(lastChannelValues[2]);

    }

    else {

      Serial.println("[!] NO SIGNAL - FAILSAFE");
    }
  }


  // mall delay to keep the control loop stable, pr else the flapping will be uncontrolled

  delay(4);
}

// SINE WAVE FLAPPING

void updateSineFlapping(int throttle) {

  // when recovering from failsafe/glide/perch,
  // restart the sine wave from the opposite side.

  if (wasFailsafe) {

    phase = PI;
    wasFailsafe = false;
  }


  // converting throttle into flapping speed.

  float speedFactor =
    map(
      throttle,
      1050,
      2000,
      60,
      100
    ) / 1000.0;


  // advance sine-wave phase.

  phase += speedFactor;


  // keeping phase between 0 and 2PI, (Yes its the 3.14150... PI)

  if (phase >= 2 * PI) {

    phase -= 2 * PI;
  }


  // calculate wing movement.

  currentOffset =
    sin(phase) * FLAP_AMPLITUDE;
}

// PERCH MODE

void updatePerchMode(int rawPitchControl) {

  wasFailsafe = true;


  // CH6 controls maximum upward angle

  float maxUpAngle =
    map(
      rawPitchControl,
      1000,
      2000,
      30,
      60
    );


  // slowly oscillating the wings

  perchPhase += 0.01;


  float goalAngle =
    maxUpAngle +
    (sin(perchPhase) * 20.0) -
    20.0;


  // smoothly moving

  if (abs(currentOffset - goalAngle) > 0.5) {

    if (currentOffset < goalAngle) {

      currentOffset += 1.5;

    }

    else {

      currentOffset -= 1.5;
    }
  }
}

// glide mode

void updateGlideMode() {

  wasFailsafe = true;


  // gradually returning the wings to the center

  if (currentOffset < 0) {

    currentOffset += 2.0;
  }

  else if (currentOffset > 0) {

    currentOffset -= 2.0;
  }


  // stop tiny movements

  if (abs(currentOffset) < 2.5) {

    currentOffset = 0;
  }
}

// FAILSAFE

void processFailsafe() {

  // slowly bringing wings back toward neutral

  if (currentOffset < 0) {

    currentOffset += 1.5;
  }

  else if (currentOffset > 0) {

    currentOffset -= 1.5;
  }


  if (abs(currentOffset) < 1.5) {

    currentOffset = 0;
  }


  // neutral servo positions

  updateServos(
    CENTER_ANGLE + (int)currentOffset,
    CENTER_ANGLE - (int)currentOffset
  );


  wasFailsafe = true;
}

// updating the servos

void updateServos(
  int targetLeft,
  int targetRight
) {

  // preventing mechanical over travel

  targetLeft =
    constrain(
      targetLeft,
      5,
      175
    );


  targetRight =
    constrain(
      targetRight,
      5,
      175
    );


  // only sending a new position when movement is required

  if (
    abs(targetLeft - lastLeftPosition) >= 1
  ) {

    servoLeft.write(targetLeft);

    lastLeftPosition = targetLeft;
  }


  if (
    abs(targetRight - lastRightPosition) >= 1
  ) {

    servoRight.write(targetRight);

    lastRightPosition = targetRight;
  }
}

/*
FlySky Receiver          Arduino Nano
--------------------------------------
PPM    ------->  D3
GND            ------->  GND

Left Servo signal ------> D9
Right Servo signal -----> D10

Servo GND --------------> GND
Servo V+ ---------------> External 5-6V supply (if not then use the arduin's channel only)

check whether your particular FlySky receiver outputs PPM, 
the code above is specifically for PPM for instance i-BUS is a different protocol and 
would require different code/wiring.

For your first bench test, keep 'FLAP_AMPLITUDE = 65' in the code 
but don't immediately run it at full throttle with the wings attached. 
first verify that both servos move symmetrically from roughly from 25 degrees to 155 degrees, 
that the transmitter controls behave correctly, 
and that the two servo directions match your physical mechanism.
*/
