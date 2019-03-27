#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 1000
#define MAX_SPEED 220//ets speed of DC motors
#define MAX_SPEED_OFFSET 20
#define pinIF A0

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
Servo myservo;
boolean goesForward=false;
int distance = 100;
int speedSet = 0;
int data;
const int number_of_measurements = 100;

void setup() {
myservo.attach(9);
myservo.write(90);
delay(1000);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
pinMode(2, INPUT);// setting pir output as arduino input
pinMode(13, OUTPUT);//setting led as output
Serial.begin(9600);//serial communication between arduino and pc
}

  int distanceR = 0;
int distanceL = 0;
delay(40);



if(distance<=30)
{
moveStop();
delay(300);
motion();
delay(400);
moveBackward();
delay(300);
moveStop();
delay(200);
distanceR = lookRight();
delay(200);
distanceL = lookLeft();
delay(200);

if(distanceR>=distanceL)
{
turnRight();
moveStop();
}else
{
turnLeft();
moveStop();
}
}else
{
moveForward();
}

distance = readPing();
}

int lookRight()
{
myservo.write(35);
delay(300);
int distance = readPing();
delay(100);
myservo.write(90);
return distance;
}

int lookLeft()
{
myservo.write(145);
delay(300);
int distance = readPing();
delay(100);
myservo.write(90);
return distance;
delay(100);
}

int readPing() {
delay(70);
int cm = sonar.ping_cm();
if(cm==0)
{
cm = 250;
}
return cm;
}
void moveStop() {
motor1.run(RELEASE);
motor2.run(RELEASE);
}
void moveForward() {

if(!goesForward)
{
goesForward=true;
motor1.run(FORWARD);
motor2.run(FORWARD);
for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
{
motor1.setSpeed(speedSet);
motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
delay(5);
}
}
}

void moveBackward() {
goesForward=false;
motor1.run(BACKWARD);
motor2.run(BACKWARD);
for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
{
motor1.setSpeed(speedSet);
motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
delay(5);
}
}

void turnRight() {
motor1.run(FORWARD);
motor2.run(BACKWARD);
delay(300);
motor1.run(FORWARD);
motor2.run(FORWARD);
}

void turnLeft() {
motor1.run(BACKWARD);
motor2.run(FORWARD);
delay(300);
motor1.run(FORWARD);
motor2.run(FORWARD);

 }