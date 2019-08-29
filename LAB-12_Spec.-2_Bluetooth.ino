#include <SoftwareSerial.h>

#define BT_TX 2
#define BT_RX 3

#define rLED  11
#define gLED  10
#define bLED  9

SoftwareSerial mySerialq(BT_TX, BT_RX);
String StringInput = "";

void setup() {
  Serial.begin(9600);
  mySerialq.begin(9600);

  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);

  setColor(255,0,0);
}

void loop() {
  
  while (mySerialq.available()){
    char charIn = (char)mySerialq.read();
    StringInput += charIn;
    delay(5);
  }

  if(!StringInput.equals("")){
    Serial.println("Receieve : " + StringInput);
    setLED(StringInput);
    StringInput = "";
  }

  // AT Command
  while (Serial.available()){
    char msg= (char) Serial.read();
    //serialSW.write(msg);
    mySerialq.write(msg);
    Serial.print(msg);
    //mySerialq.write(Serial.read());
  }
}


void setLED(String command){
  if (command=="R"){
    setColor(255, 0, 0);
  }else if (command=="G"){
    setColor(0, 255, 0);
  }else if (command=="B"){
    setColor(0, 0, 255);
  }else if (command=="AUTO"){
    while (!mySerialq.available()){
      setColor(255, 0, 0); 
      delay(100);
      setColor(0, 255, 0); 
      delay(100);
      setColor(0, 0, 255); 
      delay(100);
    }
  }
}

void setColor(int r, int g, int b){
  analogWrite(rLED, 255-r);
  analogWrite(gLED, 255-g);
  analogWrite(bLED, 255-b);
}
