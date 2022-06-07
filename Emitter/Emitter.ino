#include <RCSwitch.h>

const int buttonPin = 2;
const int analogPinX = A3;
const int analogPinY = A4;

const int treshold = 512;
const int precision = 50;

unsigned long valx = 0;
unsigned long valy = 0;
int buttonState = 0;
unsigned long key = 4;
unsigned long data =0;
RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
    // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  valx = analogRead(analogPinX);
  valy = analogRead(analogPinY);
  
  data =(key<<28) |(valx<<12) | (valy);
  mySwitch.send(data, 32);
  Serial.print("valx :");
  Serial.print(valx);
  Serial.print(", valy :");
  Serial.print(valy);
  Serial.print(", data :");
  Serial.println(data);
  //End of joystick handeling 
}
