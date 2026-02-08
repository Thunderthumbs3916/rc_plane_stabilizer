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