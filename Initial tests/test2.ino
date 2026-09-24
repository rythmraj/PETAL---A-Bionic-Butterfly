/* 
bionic butterfly code using sine wave with a amplitude as multiplicative factor and omega * time +
phase difference as the main function of the sine wave along with one horizontal angle deflection.

hardware :
arduino pro micro
flysky receiver
left servo - d9
rigth servo - d10
ppm signal - d3

rc channels:
ch1 - steering
ch2 - elevator
ch3 - flapping speed or throttle
ch5 - steering trim
ch6 - pitch trim or perch control
ch7 - perch switch

*/  
#include <Servo.h>
#include <PPMReader.h>

const byte interruptPin = 3;
const byte channelAmount = 7;
PPMReader ppm(interruptPin, channelAmount);

Servo servoLeft, servoRight;

const int centerAngle = 90;
const int flapAmplitude = 65;
const int maxPitchTrim = 20;

float phase = 0, perchPhase = 0, currentOffset = 0;
bool isPerchingState = false, wasFailsafe = true;

int lastPosL = 90, lastPosR = 90;
int lastChValues[7] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

const int ppmDeadband = 3;

unsigned long lastLogTime = 0;
const int logInterval = 1000;

void setup() {

    Serial.begin(115200);
 
    servoLeft.attach(9, 500, 2500);
    servoRight.attach(10, 500, 2500);
    servoLeft.write(centerAngle);
    servoRigth.write(centerAngle);

    serial.println("# PETAL IS READY # + # SINE WAVE MODE #")
}

int readPPMFiltered(byte ch) {
    int raw = ppm.latestValidChannelValue(ch + 1, 1500);
    if (abs(raw - lastChValues[ch]) > ppmDeadband) {
        lastChValues[ch] = raw;
    }
    return lastChValues[ch];
}

void loop() {
    unsigned long ch3Raw = 
ppm,latestValidChannelValue(3,0);
    bool isConnected = (ch3Raw != 0);

    if (!isConnected) {
        processFailsafe();  

    } else {
        int steering = readPPMFiltered(0);
        int elevator = readPPMFiltered(1);
        int throttle = readPPMFiltered(2);
        int ch5Trim = readPPMFiltered(4);
        int rawCh6 = readPPMFiltered(5);
        int ch7Switch = readPPMFiltered(6);

        int steerValue = (abs(steering - 1500) > 10) ?
    map(steering, 900, 2100, -15, 15) : 0;
        int finalSteer = steerValue + map(ch5Trim, 1000, 2000, -15, 15);
        int elevOffset = (abs(elevator - 1500) > 10) ?
    map(elevator, 900, 2100, -15, 15) : 0;
        int pitchTrim = map(rawch6, 1000, 2000, -maxPitchTrim, maxPitchTrim);

        if (throttle > 1100) isPerchingState = false;
        else if (ch7Switch > 1600 && throttle < 1100)
      isPerchingState = true;
         if (ch7Switch < 1400) isPerchingState = false;

         if (isPerchingState) {
            updateCurrentOffsetPerch(rawch6);
         }  else if (throttle < 1050) {
            updateCurrentOffsetGlide();
         }  else {
            updateCurrentOffsetSine(throttle);
         }
         
         int outL = centerAngle + (int)currentOffset + finalSteer + elevOffset + pitchTrim;
         int outR = centerAngle - (int)currentOffset + finalSteer - elevOffset - pitchTrim;

         updateServos(outL, outR); }

        if (millis() - lastLogTime > logInterval) {
            lastLogTime = millis();
            if (isConnected) {
                Serial.print("[CONNECTED] CH3: ");
        Serial.print(lastChValues[2]);
                Serial.println()
            } else {
                Serial.println("no signal from petal")
                }

            }
            dealy(4);
}

void updateCurrentOffsetSine(int throttle) {

    if (wasFailsafe) { phase = PI; wasFailsafe = false; }

    floar speedFactor = map(throttle, 1050, 2000, 60, 100)/1000.0;
    phase += speedFactor;
    if (phase >= 2*PI) phase -= 2*PI;

    currentOffset = sin(phase)*flapAmplitude;

}

void updateCurrentOffsetGlide(){
    wasFailsafe = true;
    if (currentOffset < 0) currentOffset += 2.0;
    else if (currentOffset > 0) currentOffset -= 2.0;
    if (abs(currentOffset) < 2.5) currentOffset = 0;

}

void processFailsafe(){
    if (currentOffset < 0) currentOffset += 1.5;
    else if (currentOffset > 0) currentOffset -= 1.5;
    if (abs(currentOffset) < 1.5) currentOffset = 0;
    updateServos(centerAngle + (int)currentOffset, centerAngle - (int)currentOffset);
    wasFailsafe = true;
}

void updateServos (int targetL, int targetR) {
    targetL = constrain(targetL, 5, 175);
    targetR = constrain(targetR, 5, 175);
    if (abs(targetL - lastPosL) >= 1)
    {
        servoLeft.write(targetL); lastPostL = targetL;
    }
    if (abs(targetR - lastPosR) >= 1)
    {
        servoRight.write(targetR); lastPosR = targetR;
    }

}   
