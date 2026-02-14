#include <Wire.h>
//external variables
extern const int RX_AILERON;
extern unsigned long pulseLength;
//local variables
float servoAngle;

float TXInput(){
  if (pulseLength > 0) {
    pulseLength = constrain(pulseLength, 1000, 2000); 
  }
  return pulseLength;
}

float stickIncrement() {
  float tx = TXInput();        // 1000–2000 µs
  float centered = tx - 1500;  // -500 → +500

  if (abs(centered) < 20) return 0;  // deadband

  return -centered * 0.02;   // degrees per loop(20ms)
}