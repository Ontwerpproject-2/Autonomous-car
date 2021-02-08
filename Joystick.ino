// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Joystick.ino
    Created:	08/02/2021 16:21:32
    Author:     GA\Verha
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts

//globale variabelen
const int VRx = A0;
const int VRy = A1;
int xPosition;
int yPosition;
int mapXP;
int mapYP;

//LEDS
int forward = 9;



void setup()
{
    Serial.begin(9600);

    pinMode(forward, OUTPUT)
}

// Add the main program code into the continuous loop() function
void loop()
{
    xPosition = analogRead(VRx);
    yPosition = analogRead(VRy);    
    mapXP = map(xPosition, 512, 1023, 0, 255);
    mapYP = map(yPosition, 512, 1023, 0, 255);

    Serial.print("X (1024): ");
    Serial.print(xPosition);
    Serial.print("| X (256): ");
    Serial.println(mapXP);
    //Serial.print(" | Y: ");
    //Serial.println(mapYP);
    
    analogWrite(forward, mapXP);

}
