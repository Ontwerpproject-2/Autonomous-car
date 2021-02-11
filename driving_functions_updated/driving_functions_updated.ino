#include <HCSR04.h>
//#include <Wire.h>

//Pins
const int LFmotorFW = 2;
const int LFmotorBW = 0;
const int LBmotorFW = 4;
const int LBmotorBW = 16;
const int RFmotorFW = 17;
const int RFmotorBW = 5;
const int RBmotorFW = 18;
const int RBmotorBW = 19;
const int triggerPin = 32;
const int echoPinForward =  35;
const int echoPinLeft = 34;
//SCL pin = 22 | SDA pin = 21

HCSR04 hc(triggerPin,new int[2]{echoPinForward,echoPinLeft},2);//initialisation class HCSR04 (trig pin , echo pins, number of sensors)

//Variabels
const int freq = 5000;
int moveSpeed;
float distanceForward;
float distanceLeft;
float yaw,roll,pitch,accx,accy,accz,gyrox,gyroy,gyroz,x0gy,y0gy,z0gy,xgy,ygy,zgy;
//const int GY_BNO05=0x29;

void drive(bool LF1,bool RF1,bool LB1,bool RB1,bool LF2, bool RF2, bool LB2,bool RB2, int driveSpeed){
  if(LF1==true){
    ledcWrite(0,driveSpeed);
    }else{
     ledcWrite(0,0);
     }
  if(RF1==true){
     ledcWrite(2,driveSpeed);
     }else{
      ledcWrite(2,0);
      }
   if(LB1==true){
     ledcWrite(4,driveSpeed);
     }else{
      ledcWrite(4,0);
      }
   if(RB1==true){
     ledcWrite(6,driveSpeed);
     }else{
      ledcWrite(6,0);
      }
   if(LB2==true){
    ledcWrite(1,driveSpeed);
    }else{
     ledcWrite(1,0);
     }
   if(RB2==true){
     ledcWrite(3,driveSpeed);
     }else{
      ledcWrite(3,0);
      }
   if(LF2==true){
     ledcWrite(5,driveSpeed);
     }else{
      ledcWrite(5,0);
      }
   if(RF2==true){
     ledcWrite(7,driveSpeed);
     }else{
      ledcWrite(7,0);
      }        
  }
void forward( int driveSpeed){
  drive(1,1,1,1,0,0,0,0,driveSpeed);
  }
void backward( int driveSpeed){
  drive(0,0,0,0,1,1,1,1,driveSpeed);
  }
void translateLeft( int driveSpeed){
  drive(0,1,1,0,1,0,0,1,driveSpeed);
  }
void translateRight( int driveSpeed){
  drive(1,0,0,1,0,1,1,0,driveSpeed);
  }
void turnRight( int driveSpeed){
  drive(1,0,1,0,0,1,0,1,driveSpeed);
  }
void turnLeft( int driveSpeed){
  drive(0,1,0,1,1,0,1,0,driveSpeed);
  }
void rest(){
  drive(0,0,0,0,0,0,0,0,0);
  }

void setup() { 
  /*
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
  x0gy = yaw; //startposition X,Y,Z of gyroscope
  y0gy = roll;
  z0gy = pitch;
  */
  Serial.begin(9600);  //Setting the baudrate
    
  ledcSetup(0, freq, 8);
  ledcSetup(1, freq, 8);
  ledcSetup(2, freq, 8);
  ledcSetup(3, freq, 8);
  ledcSetup(4, freq, 8);
  ledcSetup(5, freq, 8);
  ledcSetup(6, freq, 8);
  ledcSetup(7, freq, 8);
  ledcAttachPin(LFmotorFW, 0);
  ledcAttachPin(LFmotorBW, 5);
  ledcAttachPin(RFmotorFW, 2);
  ledcAttachPin(RFmotorBW, 7);
  ledcAttachPin(LBmotorFW, 4);
  ledcAttachPin(LBmotorBW, 1);
  ledcAttachPin(RBmotorFW, 6);
  ledcAttachPin(RBmotorBW, 3);
  moveSpeed = 120;
}

void loop() {
  //Ultrasound
 distanceForward = hc.dist(0);
 distanceLeft = hc.dist(1);

 Serial.print("Forward");
 Serial.print(distanceForward);
 Serial.print("| Left");
 Serial.println(distanceLeft);

 while(distanceForward >= 10)
 {
  forward(moveSpeed);
  if(distanceForward < 10)
  {
    translateLeft(moveSpeed);
    if(distanceLeft < 10)
    {
          rest();
          delay(5000);
    }

  }
 }

  //BNO055
  //gybno5();
  /*
  Serial.print("yaw=");
  Serial.print(yaw);
  Serial.print(" roll=");
  Serial.print(roll);
  Serial.print(" pitch=");
  Serial.println(pitch);
 
  Serial.print("Forward: ");
  Serial.print(distanceForward);
  Serial.print(" | Left:");
  Serial.println(distanceLeft); 
  delay(1000);
  */
}
