#include <Servo.h>

const int leftServoPin = 12;
const int rightServoPin = 0;
Servo left;
Servo right;

const int leftUSPin = 13;
float leftUSDist;

const int frontUSPin = 7;
float frontUSDist;

const int rightUSPin = 1;
float rightUSDist;

void setup() {
    initServos();
    initUltrasonics();
    Serial.begin(9600);

    Serial.println('We Are Ready to rumble!!!');
}

void draw() {
    getUSdists();

    if (frontUSDist >= 5) {
        goForward();
        keepCenter();
    } else {
        stop();
    }
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

void getUSdists() {
    leftUSDist = getLeftDist();
    frontUSDist = getFrontDist();
    rightUSDist = getRightDist();
}

float getLeftDist() {
    pinMode(leftUSPin, OUTPUT);
    digitalWrite(leftUSPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(leftUSPin, LOW);

    pinMode(leftUSPin, INPUT);
    return microsecondsToInches(pulseIn(leftUSPin, HIGH));
}

float getFrontDist() {
    pinMode(frontUSPin, OUTPUT);
    digitalWrite(frontUSPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(frontUSPin, LOW);

    pinMode(frontUSPin, INPUT);
    return microsecondsToInches(pulseIn(frontUSPin, HIGH));
}

float getRightDist() {
    pinMode(rightUSPin, OUTPUT);
    digitalWrite(rightUSPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(rightUSPin, LOW);

    pinMode(rightUSPin, INPUT);
    return microsecondsToInches(pulseIn(rightUSPin, HIGH));
}

float microsecondsToInches(float microseconds) {
    return microseconds / 74 / 2;
}

void goForward() {
    left.write(180);
    right.write(0);
}

void stop() {
    left.write(90);
    right.write(90);
}

void keepCenter() {
    // If positive we are closer to the left wall then the right and vice versa
    float fromCenter = leftUSDist - rightUSDist;
}