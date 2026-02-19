#include <Wire.h>
#include <ESP32Servo.h>
#define MPU_ADDR 0x68
//initialization
const int SERVO_PIN = 23;
const float SERVO_ZERO = 90.0;
const float SERVOTHROW = 50.0;
const float SERVO_RIGHT_MAX = SERVO_ZERO + SERVOTHROW;
const float SERVO_LEFT_MAX = SERVO_ZERO - SERVOTHROW;
const int RX_AILERON = 13;
const int RX_SWITCH = 12;
//declaration
Servo aileron;
float setRollPoint;
float getRoll();
void initImu();
void initServo();
float TXInput();
void passThrough();
float rollInputVal();
float stickIncrement();
unsigned long pulseLength, pulseLength2;
float error, correction, servoCmd;
float Kp=1;
float roll;
float stickMove;

void setup() {
  //initialization
  Serial.begin(115200);
  initImu();
  setRollPoint = getRoll();
  initServo();
  pinMode(RX_AILERON, INPUT);
  pinMode(RX_SWITCH, INPUT);
}

void loop() {
  pulseLength = pulseIn(RX_AILERON, HIGH, 30000);
  pulseLength2 = pulseIn(RX_SWITCH, HIGH, 30000);
  //Serial.println("Accelerometer: " + String(roll) + " " + String(roll-setRollPoint) + " TX Input: " + TXInput());
  if (pulseLength2 > 1500) Serial.println("1"); else Serial.println("0");
  roll = getRoll();
  if (stickIncrement() != 0){
    passThrough();
    setRollPoint = roll;
  }else{
    if (pulseLength2 > 1500){
      // P controller
      error = setRollPoint - roll;
      correction = error * Kp;

      // Send servo
      servoCmd = SERVO_ZERO + correction;
      servoCmd = constrain(servoCmd, SERVO_LEFT_MAX, SERVO_RIGHT_MAX);
      //Serial.println(
      //"Roll: " + String(roll) +
      //" Set: " + String(setRollPoint) +
      //" Err: " + String(error) +
      //" Servo: " + String(servoCmd)
      //);
      aileron.write(servoCmd);
      }else{
        passThrough();
        setRollPoint = roll;
      }
  }


  //angle hold from direct input from TX, centre of tx means plane level

  // setRollPoint = rollInputVal();

  // error = setRollPoint - roll;
  // correction = -error * Kp;
  // servoCmd = SERVO_ZERO + correction;
  // servoCmd = constrain(servoCmd, SERVO_RIGHT_MAX, SERVO_LEFT_MAX);
  // aileron.write(servoCmd);

  // Serial.println(
  //  "Roll:" + String(roll) +
  //  " Set:" + String(setRollPoint) +
  //  " Err:" + String(error) +
  //  " Servo:" + String(servoCmd)
  // );
  delay(20);
}
