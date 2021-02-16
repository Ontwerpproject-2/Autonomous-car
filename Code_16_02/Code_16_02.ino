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


void voltageCheck(){
  int voltage = analogRead(voltagePin);
  if(voltage<=3400){
    ledcWrite(8,150);
    }else{
      ledcWrite(8,0);
      
      }
  }

//This function reads in 8 bools and an int value. Each bool represents a direction for a motor in which to turn. The driveSpeed int value is an 8bit value that steers the duty cycle for the manoeuvre (speed).
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


  
//=======================================================
//BASIC MANOUVERS
//driveSpeed = dutycycle = motor speed
void forward( int driveSpeed){    //Drives forward
  drive(1,1,1,1,0,0,0,0,driveSpeed);
  }
void reverse( int driveSpeed){   //Drives backward
  drive(0,0,0,0,1,1,1,1,driveSpeed);
  }
void translateLeft( int driveSpeed){    //Slides left
  drive(0,1,1,0,1,0,0,1,driveSpeed);
  }
void translateRight( int driveSpeed){   //Slides right
  drive(1,0,0,1,0,1,1,0,driveSpeed);
  }
void turnRight( int driveSpeed){    //Rotates CW
  drive(1,0,1,0,0,1,0,1,driveSpeed);
  }
void turnLeft( int driveSpeed){   //Rotates CCW
  drive(0,1,0,1,1,0,1,0,driveSpeed);
  }
void rest(){    //Stops
  drive(0,0,0,0,0,0,0,0,0);
  }



  
//=====================================================
//Distance manouvers ran by rotary encoder

void leftSteps(int steps, int rotateSpeed){
  rest();
  int encoderCount = 0;
  int lastEncoderState = digitalRead(encoderPin);
  int encoderState = digitalRead(encoderPin);
  
  while(encoderCount<=steps){
    turnLeft(rotateSpeed);
    int encoderState = digitalRead(encoderPin);
    if (encoderState != lastEncoderState){
      if(encoderState == HIGH){
        encoderCount++;
      }
    }
    lastEncoderState = encoderState;
  }
  rest();   
}


void rightSteps(int steps, int rotateSpeed){
  rest();
  int encoderCount = 0;
  int lastEncoderState = digitalRead(encoderPin);
  int encoderState = digitalRead(encoderPin);
  
  while(encoderCount<=steps){
    turnRight(rotateSpeed);
    int encoderState = digitalRead(encoderPin);
    if (encoderState != lastEncoderState){
      if(encoderState == HIGH){
        encoderCount++;
      }
    }
    lastEncoderState = encoderState;
  }
  rest();   
}
  

//==============================================
//Ultrasone sensor
void scanningUS(int echoPin)
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH, timeOut);

  if (echoPin == echoPinForward){
    distanceForward = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  }
  
  if (echoPin == echoPinLeft){
    distanceLeft = (duration / 2) / 29.1;
  }
  
  if (echoPin == echoPinRight){
    distanceRight = (duration / 2) / 29.1;
  }
}
//=============================
//FUNCTIONS USING THE ULTRASONE SENSOR


void setParallel(int driveSpeed){
  bool leftIncrease;
  bool rightIncrease;
  bool forwardIncrease;
  scanningUS(echoPinForward);
  delay(2);
  scanningUS(echoPinLeft);
  delay(2);
  scanningUS(echoPinRight);
  delay(2); 
  int l1 = distanceLeft;
  int r1 = distanceRight;
  int f1 = distanceForward;
  rightSteps(1,moveSpeed);
  scanningUS(echoPinForward);
  delay(2);
  scanningUS(echoPinLeft);
  delay(2);
  scanningUS(echoPinRight);
  delay(2);
  int l2 = distanceLeft;
  int r2 = distanceRight;
  int f2 = distanceForward;
  if(l1 > l2){
    bool leftIncrease = false;
    }
  if(l1 <= l2){
    bool leftIncrease = true;
    }
  if(r1 > r2){
    bool rightIncrease = false;
    }
  if(r1 <= r2){
    bool rightIncrease = true;
    }
    if(f1 > f2){
    bool forwardIncrease = false;
    }
  if(f1 <= f2){
    bool forwardIncrease = true;
    }
  }




void chase(int distance,int moveSpeed,int state){
  int chaser;
  int director;
  int pass = 0;
  scanningUS(echoPinForward);
  delay(2);
  scanningUS(echoPinLeft);
  delay(2);
  scanningUS(echoPinRight);
  delay(2); 

  while(state == 1 && pass<2){
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
    
   if(chaser > 11){
       rest();
       translateLeft(moveSpeed); 
       }
    if(chaser<9){
       rest();
       translateRight(moveSpeed);
       }
    if(chaser==0){
       rest();
       }
    if(chaser>9 && chaser<11){
       if(director >11){
          forward(moveSpeed-20);
          }
        if(director <9){
          reverse(moveSpeed-20);
          }
        if(director ==0){
          rest();
          }
        if(director > 9 && director < 11){
          rest();
          pass++;
          }
        }
    }
     
   while(state == 2 && pass<2){
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
   if(chaser > 11){
    rest();
    forward(moveSpeed-20); 
    }
   if(chaser<9){
    rest();
    reverse(moveSpeed-20);
    }
   if(chaser==0){
    rest();
    }
   if(chaser>9 && chaser<11){
       if(director >11){
        translateRight(moveSpeed);
        }
       if(director <9){
        translateLeft(moveSpeed);
        }
       if(director ==0){
        rest();
        }
       if(director > 9 && director < 11){
        rest();
        pass++;
        }
     }
  }
  rest();
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
}




void loop() {

voltageCheck();
  
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
