// This file contains the test code that was used for arduino uno and sg90 servos to measure their torque and latency, motive was to check if they can be used as
// the main servos for the wings, check the code at initial_tewstcoe.ino.
// Tho, this is just a test code and not the main code for the butterfly.
// if you are building your own petal, you dont need to use this, these tests are not important, this is only for the nerds

#include <Servo.h>



Servo leftWing;
Servo rightWing;

const int LEFT_PIN = 9;
const int RIGHT_PIN = 10;

const int CENTER = 90;
const int FLAP = 25;

void setup()
{
  leftWing.attach(LEFT_PIN);
  rightWing.attach(RIGHT_PIN);

  // Start both servos at the middle
  leftWing.write(CENTER);
  rightWing.write(CENTER);

  delay(1000);
}

void loop()
{
  // Move wings upward
  for (int i = 0; i <= FLAP; i++)
  {
    leftWing.write(CENTER + i);
    rightWing.write(CENTER - i);

    delay(10);
  }

  // Move wings downward
  for (int i = FLAP; i >= -FLAP; i--)
  {
    leftWing.write(CENTER + i);
    rightWing.write(CENTER - i);

    delay(10);
  }

  // Return to the center
  for (int i = -FLAP; i <= 0; i++)
  {
    leftWing.write(CENTER + i);
    rightWing.write(CENTER - i);

    delay(10);
  }
}
