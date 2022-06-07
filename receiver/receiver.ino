/*------------------------------------------------------------------
  Roomba Control
  ==> Main commands according IRobot Open Interface doc:  http://www.irobotweb.com/~/media/MainSite/PDFs/About/STEM/Create/iRobot_Roomba_600_Open_Interface_Spec.pdf?la=enBasic
  ==> Several commands based on Create2 library developed by Dom Amato: https://github.com/brinnLabs/Create2
  Marcelo Jose Rovai - 30 June, 2016 - Visit: http://mjrobot.org
  -------------------------------------------------------------------*/

#include "roombaDefines.h"
#include <RCSwitch.h>
#include <SoftwareSerial.h>

// Roomba connection
int rxPin = 10;
int txPin = 11;
SoftwareSerial Roomba(rxPin, txPin);
RCSwitch mySwitch = RCSwitch();

//---------------------------------------------
void setup()
{
  Roomba.begin(19200);
  Serial.begin(19200);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

  pinMode(ddPin, OUTPUT);

  //delay(2000);
  Serial.println("Roomba Remote Control");

  wakeUp();   // Wake-up Roomba
  startSafe(); // Start Roomba in Safe Mode
  playSound(2);


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
  //Radio command handeling
  if (mySwitch.available()) {
    data = mySwitch.getReceivedValue();
    key = data >> 28;

    if (key == 4) {
      valx = (data >> 12) & 0xfff;
      valy = data & 0xfff;
//      Serial.print("valx :");
//      Serial.print(valx);
//      Serial.print(", valy :");
//      Serial.print(valy);
//      Serial.print(", data :");
//      Serial.println(data);
    }
    mySwitch.resetAvailable();
    if (valx < treshold - precision) {
      radius = map(valx, 0, treshold - precision, -2000, 0);
    }
    else if (valx > treshold + precision) {
      radius = map(valx, treshold + precision, 1024 , 0, 2000);
    }
    else {
      radius = 0;
    }
    //Velocity from Joystick
    if (valy < treshold - precision) {
      velocity = map(valy, 0, treshold - precision, -500, 0);
    }
    else if (valy > treshold + precision) {
      velocity = map(valy, treshold + precision, 1024 , 0, 500);
    }
    else {
      velocity = 0;
    }

      Serial.print("radius :");
      Serial.print(radius);
      Serial.print(", velocity :");
      Serial.println(velocity);
    drive (radius, velocity);
  }
  //End of Radio command handeling


}
