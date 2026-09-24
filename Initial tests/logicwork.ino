/*
so basically thats a servo for the left part or the left servo

#pin numbers:
const int LEFT_SERVO_PIN = 9;
const int RIGHT_SERVO_PIN = 10;

basically defining the pin number of each of the created objects

int - integer
so, 
int LEFT_SERVO_PIN = 9;
but what is a const

const is basically defining the object as a constant
so, if
const int LEFT_SERVO_PIN = 9;
than it means - do not change it later.
basically we are telling the arduino that this will not change later.

center position :

const int LEFT_CENTER = 90;
const int LEFT_CENTER = 90;

we are telling the arduino that when the servo is at 90 degrees, consider that the center.

typically, 0d-left - 90d-center - 180d-right

we can go with something like this as well - 55 - 90 - 125

#flapping angle

honestly, the most important variable for our experiment.

cost int FLAP_ANGLE = 35;

basically, move the servo upto 35 degrees away from its center position
hence it goes from 90 to left 55 to back to 90 to 125 to right.


#flap period

const int FLAP_PERIOD = 800;

not actually doing anything. it was intended to represent the time associated with one complete flap cycle.
but not for the test subject.

#update delay

after giving the servo a new position, wait 10millisec before giving it the next position

#setup()

void setup()
{

arduino runs this once when it starts

bascially - 

arduino turns on - setup() - initialization - loop() - loop() - loop().....

basically, before you start doing the actuall job, get everything ready.

# connecting the servo to the pin, using attach command

inside setup :
leftwing.attach(left_servo_pin);

so it means;

leftwing.attach(9)

it is - the left servos control signal is connected to arduino pin 9

attaching the left_servo_wing variable to the other object that is leftwing

#put both wings at center, using write command

leftwing.write(LEFT_CENTER)
which basically is leftwing.write(90)

also delay is the same,

delay(1000);
where it is in miliseconds

LOOPs

void loop()

basic - everything inside it repeats forever.

for (int angle =0; angle= flap agnle; angle++ )

basically, 
for loop is - repeat something while counting

for(start;condition;change)

for(
    int angle = 0;
    angle <= FLAP_ANGLE;
    anglee++ 

)


angle++ is as same as angle=angle+1
basically add 1
it maks the servo gradually moves from 90 to 125

we used for the right servo - rightwing.write(right_center - angle)

so,
angle = 0 
90-0 = 90
angle = 1
90-1=89
and so on....

we want the servos to move in opposite directions, thats why one is decreasing and the other is increasing



the final for loop;
for (int angle = -FLAP_ANGLE; angle ,<= 0; angle++)

this basically is the movement of the wing back to its initial setup

and then the loop starts again.

lets understand the program in human language:

- arduino, please learn how to control servos
- i have two servos, call one leftwing and the other one rightwing.
- the left servo is connected to pin 9
- the right servo is connected to pin 10
- their center position in 90
- i want them to move 35 degress away from the center
- when you start, put both servo at 90 degrees and wait one sec
- then repeatedly;
- move the left servo gradually from 90 towards 125
- at the same time, move the right servo from 90 to towards 55
- then move both servos through the center toward the opposite extreme
- then bring them back toawrd the center.
- and then repeat forever



important part -
#include - bring in a library
servo.h -  a library
servo - servo control object/type
int -  integer
const - constant, value shouldn't change
"=" - assign a value
void setup() - runs once
void loop() - runs forever
.attach() - connect servo to the pin
.writer() -  command servo position
delay() -  wait
for - repeat something while counting
++ - add 1
-- - subtract 1
+ - addition
- - substraction
{} - defines a block of code
// -  comment

*/
