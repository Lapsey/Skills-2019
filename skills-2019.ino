#include <Servo.h>

const int leftServoPin = 12;
const int rightServoPin = 0;
Servo left;
Servo right;

const int leftUSPin = 13;
float leftUSDur;
float leftUSDist;

const int frontUSPin = 7;
float frontUSDur;
float frontUSDist;

const int rightUSPin = 1;
float rightUSDur;
float rightUSDist;

void setup() {
    initServos();
    initUltrasonics();
    Serial.begin(9600);

    Serial.println('We Are Ready to rumble!!!');
}

void draw() {
    Serial.println('This loop does nothing right now');
}

void initServos() {
    left.attach(leftServoPin);
    right.attach(rightServoPin);

    left.write(90);
    right.write(90);
}

void initUltrasonics() {
    pinMode(leftUSPin, OUTPUT);
    pinMode(frontUSPin, OUTPUT);
    pinMode(rightUSPin, OUTPUT);
}