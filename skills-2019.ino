#include <Servo.h>

// Define the variables for the front US sensor
const int frontUsPin = 7;
float frontDur, frontDist;

// Define the variables for the left US sensor
const int leftUsPin = 13;
float leftDur, leftDist;

// Define the variables for the right US sensor
const int rightUsPin = 1;
float rightDur, rightDist;

// Define the variables for the left Servo
const int leftServoPin = 12;
Servo left;

// Define the variables for the right servo
const int rightServoPin = 0;
Servo right;

void setup() {
 initializeServos(); // Initialize the servos
 Serial.begin(9600); // Begin the serial at a 9600 BAUD rate

 Serial.println("Bot is ready to rumble"); // Print to the serial terminal that the bot is ready
}

void loop() {
  // Get all of the distances for the ultrasonic sensors
  getAllUsDistances();

  // If the closest object from the front of the bot is less than 4 inches and is not 0  
  if (frontDist <= 4 && frontDist != 0) {
    // If the left is greater that the right (We favour the left)
    if (leftDist >= rightDist) {
      Serial.println("Go Left"); // Go Left  
    } else {
      Serial.println("Go Right"); // Otherwise, go right
    }
  } else {
    Forward(); // Go Forward By default  
  }
}

void initializeServos() {
  // Atatch the servos to the correct pins
  left.attach(leftServoPin);
  right.attach(rightServoPin);

  // stop the robot when the program starts
  Stop();
}

void getAllUsDistances() {
  frontDur = getFrontDur(); // Get the duration of the front sensors ping
  frontDist = durToInches(frontDur); // Get the distance from that duration
  
  leftDur = getLeftDur(); // Same as the front sensor just with the left
  leftDist = durToInches(leftDur);

  rightDur = getRightDur(); // Same as the front sensor just with the right
  rightDist = durToInches(rightDur);
}

float getFrontDur() {
  pinMode(frontUsPin, OUTPUT); // Set the front Ping Pin to output
  digitalWrite(frontUsPin, LOW); // Write the ping pin to a low voltage
  delayMicroseconds(2); // wait 2 microseconds
  digitalWrite(frontUsPin, HIGH); // set the ping pin high
  delayMicroseconds(5); // wait 5 microseconds
  digitalWrite(frontUsPin, LOW); // set the ping pin low (This is the end of the pulse for this loop)

  pinMode(frontUsPin, INPUT); // set the ping pin to input
  return pulseIn(frontUsPin, HIGH, 15000); // return the time that ping took to get to the sensor
}

float getLeftDur() {
  pinMode(leftUsPin, OUTPUT);
  digitalWrite(leftUsPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftUsPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(leftUsPin, LOW);

  pinMode(leftUsPin, INPUT);
  return pulseIn(leftUsPin, HIGH, 15000);
}

float getRightDur() {
  pinMode(rightUsPin, OUTPUT);
  digitalWrite(rightUsPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightUsPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(rightUsPin, LOW);

  pinMode(rightUsPin, INPUT);
  return pulseIn(rightUsPin, HIGH, 15000);
}

float durToInches(float dur) {
  return dur / 74 / 2; // return the given duration as a distance measured in inches
}

void Stop() {
  left.write(90);
  right.write(90);  
}

void Forward() {
  left.write(0);
  right.write(180);  
}
