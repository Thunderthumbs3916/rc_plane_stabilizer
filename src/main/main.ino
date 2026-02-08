#include <Wire.h>
#include <ESP32Servo.h>
#define MPU_ADDR 0x68
#define SERVO_PIN 23

Servo aileron;
float setRollPoint;

void setup() {
  Serial.begin(115200);
  initImu();
  setRollPoint = getRoll();
  for (int pos = 0; pos <= 180; pos += 5) {
    aileron.write(pos);
    delay(200);
  }
}

void loop() {
  float roll = getRoll();
  Serial.println(String(roll) + " " + String(roll-setRollPoint));
  delay(100);
}