#include <Wire.h>
#include <ESP32Servo.h>
#define MPU_ADDR 0x68
//initialization
const int SERVO_PIN = 23;
const float SERVO_ZERO = 90.0;
const float SERVOTHROW = 50.0;
const float SERVO_RIGHT_MAX = 0.0+SERVOTHROW;
const float SERVO_LEFT_MAX = 180.0-SERVOTHROW;
const int RX_AILERON = 13;
//declaration
Servo aileron;
float setRollPoint;
float getRoll();
void initImu();
void initServo();
float TXInput();
void passThrough();
float rollInputVal();
unsigned long pulseLength;
float error, correction, servoCmd;
float Kp=1.0;
float roll;

void setup() {
  //initialization
  Serial.begin(115200);
  initImu();
  setRollPoint = getRoll();
  initServo();
  pinMode(RX_AILERON, INPUT);
}

void loop() {
  pulseLength = pulseIn(RX_AILERON, HIGH, 30000);
  roll = getRoll();
  Serial.println("Accelerometer: " + String(roll) + " " + String(roll-setRollPoint) + " TX Input: " + TXInput());
  setRollPoint = rollInputVal();

  error = setRollPoint - roll;
  correction = -error * Kp;
  servoCmd = SERVO_ZERO + correction;
  servoCmd = constrain(servoCmd, SERVO_RIGHT_MAX, SERVO_LEFT_MAX);
  aileron.write(servoCmd);

  Serial.println(
    "Roll:" + String(roll) +
    " Set:" + String(setRollPoint) +
    " Err:" + String(error) +
    " Servo:" + String(servoCmd)
  );
  delay(20);
}