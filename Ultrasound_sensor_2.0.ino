#include <HCSR04.h>

HCSR04 hc(22,23);//initialisation class HCSR04 (trig pin , echo pin)

void setup()
{ Serial.begin(9600); }

void loop() 
{ Serial.println( hc.dist() );
  delay(1000);
} //return current distance (cm) in serial
