/*
  pyDuino
  Master-Slave Interface for RaspberryPi and Arduino
*/

/* --- Libraries --- */
#include <Servo.h>

/* --- Pins --- */
const int SERVO_LEFT = 9;
const int SERVO_RIGHT = 10;

/* --- Constants --- */
// add constants
const int BAUD = 9600;
const int SIZE = 32;
const int SERVO_OFF = 100;
const int SERVO_CW = 200;
const int SERVO_CCW = 0;
const int INTERVAL = 20;
const int KEY = 12345;

/* --- Commands --- */
// add characters here to 
const char ID = 'I';
const char LEFT ='L';
const char RIGHT= 'R';
const char FRONT = 'F';
const char BACK = 'B';
const char WAIT = 'W';

/* --- Objects --- */
Servo left;
Servo right;
char BUFFER[SIZE];

/* --- Setup --- */
void setup() {
  Serial.begin(BAUD);
  left.attach(SERVO_LEFT);
  right.attach(SERVO_RIGHT);
  right.write(SERVO_OFF);
  left.write(SERVO_OFF);
}

/* --- Loop --- */
void loop() {
  char cmd = Serial.read();
  int resp = 0;
  switch (cmd) {
    case LEFT:
      resp = drive(200, 200, 200);
      break;
    case RIGHT:
      resp = drive(0, 0, 200);
      break;
    case FRONT:
      resp = drive(200, 0, 500);
      break;
    case BACK:
      resp = drive(0, 200, 500);
      break;
    case ID:
      resp = KEY;
    default:
      delay(INTERVAL);
      break;
  }
  
  // Write
  sprintf(BUFFER, "%d", resp);
  Serial.println(BUFFER);
  Serial.flush();
  delay(INTERVAL);
}

/* --- Drive --- */
int drive(int left_rate, int right_rate, int duration) {
  left.write(left_rate);
  right.write(right_rate);
  delay(duration);
  left.write(SERVO_OFF);
  right.write(SERVO_OFF);
  return 1;
}
