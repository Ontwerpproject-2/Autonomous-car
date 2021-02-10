const int leftBackMotor1 = 2;
const int leftBackMotor2 = 0;
const int rightBackMotor1 = 17;
const int rightBackMotor2 = 5;
const int leftFrontMotor1 = 4;
const int leftFrontMotor2 = 16;
const int rightFrontMotor1 = 18;
const int rightFrontMotor2 = 19;
const int leftButton = 25;
const int rightButton = 26;
const int VRx = 12;
const int VRy = 14;
const int speedPin = 27;
const int freq = 5000;
int moveSpeed = 255;

void drive(bool LB,bool RB,bool LF,bool RF,bool rest, int driveSpeed){
  if(LB==true){
    ledcWrite(0,driveSpeed);
    ledcWrite(1,0);
    }else{
      ledcWrite(0,0);
      ledcWrite(1,driveSpeed);
      }
   if(RB==true){
     ledcWrite(2,driveSpeed);
     ledcWrite(3,0);
     }else{
      ledcWrite(2,0);
      ledcWrite(3,driveSpeed);
      }
    if(LF==true){
     ledcWrite(4,driveSpeed);
     ledcWrite(5,0);
     }else{
      ledcWrite(4,0);
      ledcWrite(5,driveSpeed);
      }
    if(RF==true){
     ledcWrite(6,driveSpeed);
     ledcWrite(7,0);
     }else{
      ledcWrite(6,0);
      ledcWrite(7,driveSpeed);
      }
      if (rest == true){
        ledcWrite(0, 0);
        ledcWrite(1, 0);
        ledcWrite(2, 0);
        ledcWrite(3, 0);
        ledcWrite(4, 0);
        ledcWrite(5, 0);
        ledcWrite(6, 0);
        ledcWrite(7, 0);
        }          
  }




void setup() {
  Serial.begin(9600);
  ledcSetup(0, freq, 8);
  ledcSetup(1, freq, 8);
  ledcSetup(2, freq, 8);
  ledcSetup(3, freq, 8);
  ledcSetup(4, freq, 8);
  ledcSetup(5, freq, 8);
  ledcSetup(6, freq, 8);
  ledcSetup(7, freq, 8);
  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
  ledcAttachPin(leftBackMotor1, 0);
  ledcAttachPin(leftBackMotor2, 1);
  ledcAttachPin(rightBackMotor1, 2);
  ledcAttachPin(rightBackMotor2, 3);
  ledcAttachPin(leftFrontMotor1, 4);
  ledcAttachPin(leftFrontMotor2, 5);
  ledcAttachPin(rightFrontMotor1, 6);
  ledcAttachPin(rightFrontMotor2, 7);

}

void loop() {
  int Xval = analogRead(VRx);
  int Yval = analogRead(VRy);
  bool rightButtonState = digitalRead(rightButton);
  bool leftButtonState = digitalRead(leftButton);
  moveSpeed = analogRead(speedPin)/16;
  Serial.println(moveSpeed);
  if(Yval <= 1800){
      drive(0,0,0,0,0,moveSpeed);
      Yval = analogRead(VRy);
      moveSpeed = analogRead(speedPin)/16;
      Serial.println(moveSpeed);
  }
  if (Yval >= 1900){
      drive(1,1,1,1,0,moveSpeed);
      Yval = analogRead(VRy);
      moveSpeed = analogRead(speedPin)/16;
      Serial.println(moveSpeed);
  }
   if (Yval >1800 && Yval <1900){
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      ledcWrite(2, 0);
      ledcWrite(3, 0);
      ledcWrite(4, 0);
      ledcWrite(5, 0);
      ledcWrite(6, 0);
      ledcWrite(7, 0);
      Yval = analogRead(VRy);
      moveSpeed = analogRead(speedPin)/16;
      Serial.println(moveSpeed);  
  }
  if(Xval <= 1800){
    drive(0,1,1,0,0,moveSpeed);
      Xval = analogRead(VRx);
      moveSpeed = analogRead(speedPin)/16;
      Serial.println(moveSpeed);
    }
     if(Xval >= 1900){
    drive(1,0,0,1,0,moveSpeed);
      Xval = analogRead(VRx);
      moveSpeed = analogRead(speedPin)/16;
      Serial.println(moveSpeed);
    }
    if(rightButtonState== true){
      drive(1,0,1,0,0,moveSpeed);
      rightButtonState = digitalRead(rightButton);
      moveSpeed = analogRead(speedPin)/16;
      Serial.println(moveSpeed);
    }
        if(leftButtonState== true){
    drive(0,1,0,1,0,moveSpeed);
      leftButtonState = digitalRead(leftButton);
      moveSpeed = analogRead(speedPin)/16;
      Serial.println(moveSpeed);
    }
    
}
