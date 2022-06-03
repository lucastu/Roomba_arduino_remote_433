/*------------------------------------------------------------------
  Roomba Control 
  ==> Main commands according IRobot Open Interface doc:  http://www.irobotweb.com/~/media/MainSite/PDFs/About/STEM/Create/iRobot_Roomba_600_Open_Interface_Spec.pdf?la=enBasic 
  ==> Several commands based on Create2 library developed by Dom Amato: https://github.com/brinnLabs/Create2
  Marcelo Jose Rovai - 30 June, 2016 - Visit: http://mjrobot.org
-------------------------------------------------------------------*/

#include "roombaDefines.h"
#include <SoftwareSerial.h>

// Roomba connection
int rxPin=10;
int txPin=11;
SoftwareSerial Roomba(rxPin,txPin);

//---------------------------------------------
void setup() 
{
  Roomba.begin(19200);
  Serial.begin(19200);
  
  pinMode(ddPin, OUTPUT);
  //pinMode(ledPin, OUTPUT); //spare if needed for test purpose

  delay(2000);
  Serial.print("Roomba Remote Control");
  
  wakeUp();   // Wake-up Roomba
  startSafe(); // Start Roomba in Safe Mode

  // turn-off all LEDs and Display
  setPowerLED(128,0);
  setDebrisLED(OFF);
  setDockLED(OFF);
  setSpotLED(OFF);
  setWarningLED(OFF);
  cleanDigitLED ();

  //playSound (1); // start sound
  setDebrisLED(OFF);
  //writeLEDs ('s', 't', 'o', 'p');
  
   playSound (2);

  
  //drive (motorSpeed, 0);
  //driveRight(motorSpeed);
  //driveLeft(motorSpeed);
  
  //motorSquareTest(); // un-comment if you want to test Roomba doing a square 
  //turnCW (40, 180);  //un-comment if you want to test Roomba spin clock-wise 180 degrees and stop
  //driveWheels(20, -20); //un-comment if you want to test Roomba spin
  //driveLeft(20); //un-comment if you want to test Roomba turning left 

 Serial.println("Init over");
}

void loop() 
{
  //velocity, -500, 500); //def max and min velocity in mm/s
  //radius, -2000, 2000); //def max and min radius in mm
  
  buttonState = digitalRead(buttonPin);
  valx = analogRead(analogPinX);
  valy = analogRead(analogPinY);
  
  //Radius from Joystick
  if (valx < treshold-precision){
      radius = map(valx, 0, treshold-precision, -2000, 0);
  }
  else if (valx > treshold+precision){
      radius = map(valx, treshold+precision, 1024 , 0, 2000);
  }
  else {
    radius = 0;
      
  //Velocity from Joystick 
  if (valy < treshold-precision){
      velocity = map(valy, 0, treshold-precision, -500, 0);
  }
  else if (valy > treshold+precision){
      velocity = map(valy, treshold+precision, 1024 , 0, 5000);
  }
  else{
    velocity = 0;
  }
  //End of joystick handeling 
  drive (radius, velocity);  

}
