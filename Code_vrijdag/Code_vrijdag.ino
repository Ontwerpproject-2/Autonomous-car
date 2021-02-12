//assigning pins to each motor direction going to the H-bridge
const int LFmotorFW = 2;
const int LFmotorBW = 0;
const int LBmotorFW = 4;
const int LBmotorBW = 16;
const int RFmotorFW = 17;
const int RFmotorBW = 5;
const int RBmotorFW = 18;
const int RBmotorBW = 19;

//assigning pins to the sensor inputs
const int encoderPin = 33; //input from optical rotary encoder
const int freq = 5000; //set frequency for the outgoing PWM signals
int moveSpeed; 
volatile int encoderCount;
volatile int revolutionCount;
const int trigPin = 32;    // Trigger
const int echoPinForward = 34;// Echo
const int echoPinBack = 35;
long duration, distanceForward, distanceBackward;
long timeOut = 10000;


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
//MANOUVERS
//driveSpeed = dutycycle = motor speed

void forward( int driveSpeed){    //Drives forward
  drive(1,1,1,1,0,0,0,0,driveSpeed);
  }
void backward( int driveSpeed){   //Drives backward
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

//Interrupt function for optical rotary encoder
void IRAM_ATTR encoderVal(){
  encoderCount++;
  if(encoderCount == 20){
    revolutionCount++;
    encoderCount = 0;
    Serial.println(revolutionCount);
    }
  }

//==============================================
//Ultrasone sensor
void ScanningUS(int echoPin)
{
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

  if (echoPin == echoPinForward)
  {
    // Convert the time into a distance
    distanceForward = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    if(distanceForward == 0)
    {
      rest();
    }
  }

  if (echoPin == echoPinBack)
  {
    distanceBackward = (duration / 2) / 29.1;
    if(distanceForward == 0)
    {
      rest();
    }
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(encoderPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinForward, INPUT);
  pinMode(echoPinBack, INPUT);

  //assign PWM-channels with a corresponding frequency and resolution
  ledcSetup(0, freq, 8);
  ledcSetup(1, freq, 8);
  ledcSetup(2, freq, 8);
  ledcSetup(3, freq, 8);
  ledcSetup(4, freq, 8);
  ledcSetup(5, freq, 8);
  ledcSetup(6, freq, 8);
  ledcSetup(7, freq, 8);
  
  //assign PWM channels to corresponding pin
  ledcAttachPin(LFmotorFW, 0);
  ledcAttachPin(LFmotorBW, 5);
  ledcAttachPin(RFmotorFW, 2);
  ledcAttachPin(RFmotorBW, 7);
  ledcAttachPin(LBmotorFW, 4);
  ledcAttachPin(LBmotorBW, 1);
  ledcAttachPin(RBmotorFW, 6);
  ledcAttachPin(RBmotorBW, 3);
  //Declare speed
  moveSpeed = 255;
  attachInterrupt(digitalPinToInterrupt(encoderPin), encoderVal, RISING);
}

void loop() {
int a = digitalRead(encoderPin);
ScanningUS(echoPinForward);
ScanningUS(echoPinBack);
Serial.print("F: ");
Serial.print(distanceForward);
Serial.print(" |B: ");
Serial.println(distanceBackward);

//if(revolutionCount<=1){
//  translateLeft(140);
//  }else{
//    drive(1,1,1,1,1,1,1,1,100);
//    delay(200);
//    rest();
//    delay(5000);
//    revolutionCount = 0;
//    encoderCount = 0;
//    }
//if(revolutionCount<=1){
//  for(int i = 0;i<=moveSpeed;i++){
//    forward(i);
//    delay(50);
//  }
//  forward(moveSpeed);
//  }else{
//    rest();
//    delay(1000);
//    revolutionCount=0;
//    }/
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
