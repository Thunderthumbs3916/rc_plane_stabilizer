#include <Wire.h>
#define MPU_ADDR 0x68

float setRollPoint;

void setup() {
  Serial.begin(115200);
  initImu();
  setRollPoint = getRoll();
}

void loop() {
  float roll = getRoll();
  Serial.println(String(roll) + " " + String(roll-setRollPoint));
  delay(100);
}