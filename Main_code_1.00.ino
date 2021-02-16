#include <Wire.h>
float yaw, roll, pitch, accx, accy, accz, gyrox, gyroy, gyroz, x0gy, y0gy, z0gy, xgy, ygy, zgy, yaw0, roll0, pitch0, rotateAngel;
const int GY_BNO05 = 0x29;

//assigning pins to each motor direction going to the H-bridge
const int LFmotorFW = 2;
const int LFmotorBW = 0;
const int LBmotorFW = 4;
const int LBmotorBW = 16;
const int RFmotorFW = 17;
const int RFmotorBW = 5;
const int RBmotorFW = 18;
const int RBmotorBW = 19;
const int buzzerPin = 15;
const int voltagePin = 13;

const int encoderPin = 33; //input from rotary encoder
const int trigPin = 32;    // Trigger
const int echoPinForward = 35;// Echo
const int echoPinLeft = 34;
const int echoPinRight = 25;
const int freq = 5000;//set frequency for the outgoing PWM signals
long duration, distanceForward, distanceLeft, distanceRight;
long timeOut = 10000;
int moveSpeed;


void voltageCheck() {
  int voltage = analogRead(voltagePin);
  if (voltage <= 3400) {
    ledcWrite(8, 150);
  } else {
    ledcWrite(8, 0);

  }
}

//This function reads in 8 bools and an int value. Each bool represents a direction for a motor in which to turn. The driveSpeed int value is an 8bit value that steers the duty cycle for the manoeuvre (speed).
void drive(bool LF1, bool RF1, bool LB1, bool RB1, bool LF2, bool RF2, bool LB2, bool RB2, int driveSpeed) {
  if (LF1 == true) {
    ledcWrite(0, driveSpeed);
  } else {
    ledcWrite(0, 0);
  }
  if (RF1 == true) {
    ledcWrite(2, driveSpeed);
  } else {
    ledcWrite(2, 0);
  }
  if (LB1 == true) {
    ledcWrite(4, driveSpeed);
  } else {
    ledcWrite(4, 0);
  }
  if (RB1 == true) {
    ledcWrite(6, driveSpeed);
  } else {
    ledcWrite(6, 0);
  }
  if (LB2 == true) {
    ledcWrite(1, driveSpeed);
  } else {
    ledcWrite(1, 0);
  }
  if (RB2 == true) {
    ledcWrite(3, driveSpeed);
  } else {
    ledcWrite(3, 0);
  }
  if (LF2 == true) {
    ledcWrite(5, driveSpeed);
  } else {
    ledcWrite(5, 0);
  }
  if (RF2 == true) {
    ledcWrite(7, driveSpeed);
  } else {
    ledcWrite(7, 0);
  }
}



//=======================================================
//BASIC MANOUVERS
//driveSpeed = dutycycle = motor speed
void forward( int driveSpeed) {   //Drives forward
  drive(1, 1, 1, 1, 0, 0, 0, 0, driveSpeed);
}
void reverse( int driveSpeed) {  //Drives backward
  drive(0, 0, 0, 0, 1, 1, 1, 1, driveSpeed);
}
void translateLeft( int driveSpeed) {   //Slides left
  drive(0, 1, 1, 0, 1, 0, 0, 1, driveSpeed);
}
void translateRight( int driveSpeed) {  //Slides right
  drive(1, 0, 0, 1, 0, 1, 1, 0, driveSpeed);
}
void turnRight( int driveSpeed) {   //Rotates CW
  drive(1, 0, 1, 0, 0, 1, 0, 1, driveSpeed);
}
void turnLeft( int driveSpeed) {  //Rotates CCW
  drive(0, 1, 0, 1, 1, 0, 1, 0, driveSpeed);
}
void rest() {   //Stops
  drive(0, 0, 0, 0, 0, 0, 0, 0, 0);
}




//=====================================================
//Distance manouvers ran by rotary encoder

void leftSteps(int steps, int rotateSpeed) {
  rest();
  int encoderCount = 0;
  int lastEncoderState = digitalRead(encoderPin);
  int encoderState = digitalRead(encoderPin);

  while (encoderCount <= steps) {
    turnLeft(rotateSpeed);
    int encoderState = digitalRead(encoderPin);
    if (encoderState != lastEncoderState) {
      if (encoderState == HIGH) {
        encoderCount++;
      }
    }
    lastEncoderState = encoderState;
  }
  rest();
}


void rightSteps(int steps, int rotateSpeed) {
  rest();
  int encoderCount = 0;
  int lastEncoderState = digitalRead(encoderPin);
  int encoderState = digitalRead(encoderPin);

  while (encoderCount <= steps) {
    turnRight(rotateSpeed);
    int encoderState = digitalRead(encoderPin);
    if (encoderState != lastEncoderState) {
      if (encoderState == HIGH) {
        encoderCount++;
      }
    }
    lastEncoderState = encoderState;
  }
  rest();
}


//==============================================
//Ultrasone sensor
float ScanningUS(int echoPin)
{
  float distance;
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH, timeOut);
  distance = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343

  return distance;
}

//=============================
//FUNCTIONS USING THE ULTRASONE SENSOR


void setParallel(int driveSpeed) {
  bool leftIncrease;
  bool rightIncrease;
  bool forwardIncrease;
  //Normaal gezien werkt het nu zonder de delay
  distanceForward = scanningUS(echoPinForward);
  //delay(2);
  distanceLeft = scanningUS(echoPinLeft);
  //delay(2);
  distanceRight = scanningUS(echoPinRight);
  //delay(2);
  int l1 = distanceLeft;
  int r1 = distanceRight;
  int f1 = distanceForward;
  rightSteps(1, moveSpeed);
  distanceForward = scanningUS(echoPinForward);
  //delay(2);
  scanningUS(echoPinLeft);
  //delay(2);
  scanningUS(echoPinRight);
  //delay(2);
  int l2 = distanceLeft;
  int r2 = distanceRight;
  int f2 = distanceForward;
  if (l1 > l2) {
    bool leftIncrease = false;
  }
  if (l1 <= l2) {
    bool leftIncrease = true;
  }
  if (r1 > r2) {
    bool rightIncrease = false;
  }
  if (r1 <= r2) {
    bool rightIncrease = true;
  }
  if (f1 > f2) {
    bool forwardIncrease = false;
  }
  if (f1 <= f2) {
    bool forwardIncrease = true;
  }
}

void chase(int distance, int moveSpeed, int state) {
  int chaser;
  int director;
  int pass = 0;
  scanningUS(echoPinForward);
  delay(2);
  scanningUS(echoPinLeft);
  delay(2);
  scanningUS(echoPinRight);
  delay(2);

  while (state == 1 && pass < 2) {
    scanningUS(echoPinForward);
    delay(2);
    scanningUS(echoPinLeft);
    delay(2);
    scanningUS(echoPinRight);
    delay(2);
    chaser = distanceLeft;
    director = distanceForward;
    Serial.print("F1: ");
    Serial.print(distanceForward);
    Serial.print(" |L1: ");
    Serial.print(distanceLeft);
    Serial.print(" |R1: ");
    Serial.println(distanceRight);

    if (chaser > 11) {
      rest();
      translateLeft(moveSpeed);
    }
    if (chaser < 9) {
      rest();
      translateRight(moveSpeed);
    }
    if (chaser == 0) {
      rest();
    }
    if (chaser > 9 && chaser < 11) {
      if (director > 11) {
        forward(moveSpeed - 20);
      }
      if (director < 9) {
        reverse(moveSpeed - 20);
      }
      if (director == 0) {
        rest();
      }
      if (director > 9 && director < 11) {
        rest();
        pass++;
      }
    }
  }

  while (state == 2 && pass < 2) {
    scanningUS(echoPinForward);
    delay(2);
    scanningUS(echoPinLeft);
    delay(2);
    scanningUS(echoPinRight);
    delay(2);
    chaser = distanceForward;
    director = distanceRight;
    Serial.print("F2: ");
    Serial.print(distanceForward);
    Serial.print(" |L2: ");
    Serial.print(distanceLeft);
    Serial.print(" |R2: ");
    Serial.println(distanceRight);
    if (chaser > 11) {
      rest();
      forward(moveSpeed - 20);
    }
    if (chaser < 9) {
      rest();
      reverse(moveSpeed - 20);
    }
    if (chaser == 0) {
      rest();
    }
    if (chaser > 9 && chaser < 11) {
      if (director > 11) {
        translateRight(moveSpeed);
      }
      if (director < 9) {
        translateLeft(moveSpeed);
      }
      if (director == 0) {
        rest();
      }
      if (director > 9 && director < 11) {
        rest();
        pass++;
      }
    }
  }
  rest();
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

void rotate2(long rotateAngle)
{
  gybno5();
  long startYaw = yaw;
  long endAngle = startYaw + rotateAngle;

  if (endAngle >= 360)
  {
    endAngle = endAngle - 360;
    //Turn right until over 0
    while ( yaw > 90)
    {
      //Turn Right
      gybno5();
      Serial.print("TURN RIGHT  ");
      Serial.print("endAngle= ");
      Serial.print(endAngle);
      Serial.print("| yaw=");
      Serial.println(yaw);
      delay(1000);
    }
  }

  if (endAngle < 0)
  {
    endAngle = endAngle + 360;
    //Turn left
    while (yaw < 270)
    {
      //Turn Left
      gybno5();
      Serial.print("TURN LEFT  ");
      Serial.print("endAngle= ");
      Serial.print(endAngle);
      Serial.print("| yaw= ");
      Serial.println(yaw);
      delay(1000);
    }
  }

  //Turn with 1 degree ofsett
  while ((endAngle - 1 > yaw) || (endAngle + 1 < yaw))
  {
    //Turn right if goes to far
    if (endAngle - 1 > yaw)
    {
      //Turn Right
      gybno5();
      Serial.print("TURN RIGHT  ");
      Serial.print("endAngle= ");
      Serial.print(endAngle);
      Serial.print("| yaw=");
      Serial.println(yaw);
      delay(1000);
    }
    if (endAngle + 1 < yaw)
    {
      //Turn Left
      gybno5();
      Serial.print("TURN LEFT  ");
      Serial.print("endAngle= ");
      Serial.print(endAngle);
      Serial.print("| yaw= ");
      Serial.println(yaw);
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(encoderPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinForward, INPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(voltagePin, INPUT);
  digitalWrite(trigPin, LOW);

  //assign PWM-channels with a corresponding frequency and resolution
  ledcSetup(0, freq, 8);
  ledcSetup(1, freq, 8);
  ledcSetup(2, freq, 8);
  ledcSetup(3, freq, 8);
  ledcSetup(4, freq, 8);
  ledcSetup(5, freq, 8);
  ledcSetup(6, freq, 8);
  ledcSetup(7, freq, 8);
  ledcSetup(8, freq, 8);

  //assign PWM channels to corresponding pin
  ledcAttachPin(LFmotorFW, 0);
  ledcAttachPin(LFmotorBW, 5);
  ledcAttachPin(RFmotorFW, 2);
  ledcAttachPin(RFmotorBW, 7);
  ledcAttachPin(LBmotorFW, 4);
  ledcAttachPin(LBmotorBW, 1);
  ledcAttachPin(RBmotorFW, 6);
  ledcAttachPin(RBmotorBW, 3);

  ledcAttachPin(buzzerPin, 8);
  //Declare speed
  moveSpeed = 110;

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
}

//States
int state = 1;

/* State discription
  1- scan
  2- what to do
  3- drive
  4- battery check
*/

void loop() {
  if (state == 1)
  {
    //Insert all scanning sensors here

    //BNO055
    gybno5();

    //Ultrasoundsensors
    ScanningUS(echoPinForward);
    ScanningUS(echoPinLeft);
    ScanningUS(echoPinRight);
  }
  if (state == 2)
  {
    //Insert all drive commands here
  }
  if (state == 3)
  {
    //Insert the driving itself here
  }
  if (state == 4)
  {
    voltageCheck();
  }



  //forward(50);
  //delay(1000);
  //forward(100);
  //delay(1000);
  //forward(150);
  //delay(1000);
  //forward(200);
  //delay(1000);
  //forward(255);
  //delay(1000);
  //forward(110);
  //delay(1000);
  //leftSteps(1,moveSpeed);
  //delay(2000);


  //chase(10,moveSpeed,1);
  //chase(10,moveSpeed,2);
  //delay(3000);
  //Serial.print("F: ");
  //Serial.print(distanceForward);
  //Serial.print(" |L: ");
  //Serial.print(distanceLeft);
  //Serial.print(" |R: ");
  //Serial.println(distanceRight);


  //  for(int i =100;i<=moveSpeed;i++){
  //    forward(i);
  //    delay(5);
  //  }
  //  forward(moveSpeed);
  //  delay(500);
  //  for(int i = moveSpeed;i>=100;i--){
  //    forward(i);
  //    delay(5);
  //  }
  //  forward(60);
  //  delay(5000);
}
