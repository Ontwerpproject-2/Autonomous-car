const int LFmotorFW = 2;
const int LFmotorBW = 0;
const int LBmotorFW = 4;
const int LBmotorBW = 16;
const int RFmotorFW = 17;
const int RFmotorBW = 5;
const int RBmotorFW = 18;
const int RBmotorBW = 19;
const int freq = 5000;
int moveSpeed;


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
     drive(0,1,0,0,1,0,0,0,moveSpeed);

}
