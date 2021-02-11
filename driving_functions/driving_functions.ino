const int leftBackMotor1 = 2;
const int leftBackMotor2 = 0;
const int rightBackMotor1 = 17;
const int rightBackMotor2 = 5;
const int leftFrontMotor1 = 4;
const int leftFrontMotor2 = 16;
const int rightFrontMotor1 = 18;
const int rightFrontMotor2 = 19;
const int freq = 5000;
int moveSpeed = 0;


void drive(bool LB1,bool RB1,bool LF1,bool RF1,bool LB2, bool RB2, bool LF2,bool RF2, int driveSpeed){
  if(LB1==true){
    ledcWrite(0,driveSpeed);
    }else{
     ledcWrite(0,0);
     }
  if(RB1==true){
     ledcWrite(2,driveSpeed);
     }else{
      ledcWrite(2,0);
      }
   if(LF1==true){
     ledcWrite(4,driveSpeed);
     }else{
      ledcWrite(4,0);
      }
   if(RF1==true){
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
  drive(1,0,1,0,0,1,0,1,driveSpeed);
  }
void translateRight( int driveSpeed){
  drive(0,1,0,1,1,0,1,0,driveSpeed);
  }
void turnRight( int driveSpeed){
  drive(1,1,0,0,0,0,1,1,driveSpeed);
  }
void turnLeft( int driveSpeed){
  drive(0,0,1,1,1,1,0,0,driveSpeed);
  }
void rest(){
  drive(0,0,0,0,0,0,0,0,0);
  }




void setup() {
  ledcSetup(0, freq, 8);
  ledcSetup(1, freq, 8);
  ledcSetup(2, freq, 8);
  ledcSetup(3, freq, 8);
  ledcSetup(4, freq, 8);
  ledcSetup(5, freq, 8);
  ledcSetup(6, freq, 8);
  ledcSetup(7, freq, 8);
  ledcAttachPin(leftBackMotor1, 0);
  ledcAttachPin(leftBackMotor2, 1);
  ledcAttachPin(rightBackMotor1, 2);
  ledcAttachPin(rightBackMotor2, 3);
  ledcAttachPin(leftFrontMotor1, 4);
  ledcAttachPin(leftFrontMotor2, 5);
  ledcAttachPin(rightFrontMotor1, 6);
  ledcAttachPin(rightFrontMotor2, 7);
  moveSpeed = 150;

}

void loop() {
  delay(5000);
  forward(moveSpeed);
  delay(500);
  turnLeft(moveSpeed);
  delay(500);
  turnRight(moveSpeed);
  delay(500);
  translateLeft(moveSpeed);
  delay(500);
  translateRight(moveSpeed);
  delay(500);
  rest();
}
