// Connect GND, S1 and SR pins together.
#include <Wire.h>
float yaw, roll, pitch, accx, accy, accz, gyrox, gyroy, gyroz, x0gy, y0gy, z0gy, xgy, ygy, zgy, yaw0, roll0, pitch0;
const int GY_BNO05 = 0x29;
void setup()
{
  //I2C communication
  Wire.begin();
  Wire.setClock(400000);
  delay(100);
  Wire.beginTransmission(GY_BNO05);
  Wire.write(0x3E); // Power Mode
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);
  Wire.beginTransmission(GY_BNO05);
  Wire.write(0x3D); // Operation Mode
  Wire.write(0x0C); //NDOF:0X0C (or B1100) , IMU:0x08 (or B1000) , NDOF_FMC_OFF: 0x0B (or B1011)
  Wire.endTransmission();
  delay(100);
  gybno5();

  //startposition of the Euler angles
  yaw0 = yaw;
  roll0 = roll;
  pitch0 = pitch;

  Serial.begin(9600);  //Setting the baudrate
}

void gybno5() {
  Wire.beginTransmission(GY_BNO05);
  Wire.write(0x08);
  Wire.endTransmission(false);
  Wire.requestFrom(GY_BNO05, 32, true);
  // Accelerometer
  accx = (int16_t)(Wire.read() | Wire.read() << 8 ) / 100.00; // m/s^2
  accy = (int16_t)(Wire.read() | Wire.read() << 8 ) / 100.00; // m/s^2
  accz = (int16_t)(Wire.read() | Wire.read() << 8 ) / 100.00; // m/s^2
  // Magnetometer
  (Wire.read() | Wire.read() << 8 );
  (Wire.read() | Wire.read() << 8 );
  (Wire.read() | Wire.read() << 8 );
  // Gyroscope
  gyrox = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // Dps
  gyroy = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // Dps
  gyroz = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // Dps
  // Euler Angles
  yaw = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; //in Degrees unit
  roll = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; //in Degrees unit
  pitch = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; //in Degrees unit
  // Quaternions
  (Wire.read() | Wire.read() << 8 );
  (Wire.read() | Wire.read() << 8 );
  (Wire.read() | Wire.read() << 8 );
  (Wire.read() | Wire.read() << 8 );
}


void loop()
{
  gybno5();
  // Print data
  /*
    Serial.print("Yaw=");
    Serial.print(accx  );
    Serial.print(" Roll=");
    Serial.print(accy);
    Serial.print(" Pitch=");
    Serial.println(accz);
    delay(300);
  */
  Serial.print("yawStart=");
  Serial.print(yaw0);
  Serial.print(" rollStart=");
  Serial.print(roll0);
  Serial.print(" pitchStart=");
  Serial.println(pitch0);
  Serial.print("yaw=");
  Serial.print(yaw);
  Serial.print(" roll=");
  Serial.print(roll);
  Serial.print(" pitch=");
  Serial.println(pitch);

  delay(1000);
}
