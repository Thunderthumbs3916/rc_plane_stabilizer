#define MPU_ADDR 0x68
//local variables
float Ax, Ay, Az, pitch;

void initImu(){
  Serial.begin(115200);

  Wire.begin(21, 22);        // START I2C
  Wire.setClock(100000);     // safer for MPU6050 clones

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);          // PWR_MGMT_1
  Wire.write(0);             // wake up
  Wire.endTransmission();

  Serial.println("MPU6050 ready");
}


float getRoll() {
  // Tell MPU6050 we want to read accelerometer data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);   // ACCEL_XOUT_H register
  Wire.endTransmission(false);

  // Request 6 bytes: Ax, Ay, Az (each is 2 bytes)
  Wire.requestFrom(MPU_ADDR, 6, true);

  int16_t rawAx = Wire.read() << 8 | Wire.read();
  int16_t rawAy = Wire.read() << 8 | Wire.read();
  int16_t rawAz = Wire.read() << 8 | Wire.read();

  // Convert raw values to g's
  Ax = rawAx / 16384.0;
  Ay = rawAy / 16384.0;
  Az = rawAz / 16384.0;

  // Calculate roll angle (degrees)
  float roll = atan2(Ay, Az) * 180.0 / PI;

  return roll;   // send value back to loop()
}


// void setup() {
//   //Serial.begin(115200);
//   Wire.begin(21, 22);   // ESP32 SDA, SCL

//   // Wake up MPU6050
//   Wire.beginTransmission(MPU_ADDR);
//   Wire.write(0x6B);     // PWR_MGMT_1
//   Wire.write(0);        // wake up
//   Wire.endTransmission();

//   Serial.println("MPU6050 ready");
// }

// void loop() {
//   Wire.beginTransmission(MPU_ADDR);
//   Wire.write(0x3B);   // ACCEL_XOUT_H
//   Wire.endTransmission(false);
//   Wire.requestFrom(MPU_ADDR, 6, true);

//   int16_t rawAx = Wire.read() << 8 | Wire.read();
//   int16_t rawAy = Wire.read() << 8 | Wire.read();
//   int16_t rawAz = Wire.read() << 8 | Wire.read();

//   Ax = rawAx / 16384.0;
//   Ay = rawAy / 16384.0;
//   Az = rawAz / 16384.0;

//   roll  = atan2(Ay, Az) * 180 / PI;
//   pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180 / PI;

//   //Serial.print("Roll: ");
//   //Serial.print(roll);
//   //Serial.print(" | Pitch: ");
//   //Serial.println(pitch);

//   delay(100);
// }