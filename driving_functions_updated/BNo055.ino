/*
void gybno5(){
  Wire.beginTransmission(GY_BNO05);
  Wire.write(0x08); 
  Wire.endTransmission(false);
  Wire.requestFrom(GY_BNO05,32,true);
  // Accelerometer
  accx=(int16_t)(Wire.read()|Wire.read()<<8 )/100.00; // m/s^2
  accy=(int16_t)(Wire.read()|Wire.read()<<8 )/100.00; // m/s^2
  accz=(int16_t)(Wire.read()|Wire.read()<<8 )/100.00; // m/s^2
  // Magnetometer
  (Wire.read()|Wire.read()<<8 ); 
  (Wire.read()|Wire.read()<<8 ); 
  (Wire.read()|Wire.read()<<8 ); 
  // Gyroscope
  gyrox=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // Dps
  gyroy=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // Dps
  gyroz=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // Dps
  // Euler Angles
  yaw=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00;  //in Degrees unit
  roll=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00;  //in Degrees unit
  pitch=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00;  //in Degrees unit
  // Quaternions
  (Wire.read()|Wire.read()<<8 );
  (Wire.read()|Wire.read()<<8 );
  (Wire.read()|Wire.read()<<8 );
  (Wire.read()|Wire.read()<<8 );
}
*/
