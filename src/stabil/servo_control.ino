#include <Wire.h>
#include <ESP32Servo.h>
//external variables
extern const int SERVO_PIN;
extern const float SERVO_ZERO;
extern const float SERVO_RIGHT_MAX;
extern const float SERVO_LEFT_MAX;
extern const float SERVOTHROW;

extern Servo aileron;

void initServo(){
  aileron.attach(SERVO_PIN);
  aileron.write(SERVO_ZERO);
}

void passThrough(){
  aileron.write(map(TXInput(), 1000, 2000, 0+SERVOTHROW, 180-SERVOTHROW));
  delay(100);
}

float rollInputVal(){
  return map(TXInput(), 1000, 2000, -70, 70);
}