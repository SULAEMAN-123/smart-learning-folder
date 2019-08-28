#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>


#define VIB_SENSOR A0
#define TOUCH 1

IoTMakers im;

#define deviceID    "k19740D1566970921312"
#define authnRqtNo  "jcpq7suhj"
#define extrSysID   "OPEN_TCP_001PTL001_1000007623"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2
#define TAG_ID "PIEZO"

int AnalogMeasure;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VIB_SENSOR, INPUT);
  initIoTMakers();
}

void initIoTMakers(){
  while (1){
    Serial.print(F("Connecting to AP . . ."));

    while (im.begin(WIFI_SSID, WIFI_PASS) <0 ) {
      Serial.println(F("Retrying..."));
      delay (100);
    }

    Serial.println("Success");
    im.init(deviceID, authnRqtNo, extrSysID);
    Serial.println(F("Connect to platform ..."));

    while (im.connect() <0 ){
      Serial.println(F("Retrying..."));
      delay (100);
    }

    Serial.println(F("Success"));
    Serial.println(F("Auth..."));

    if (im.auth_device() >= 0){
      Serial.println(F("Success"));
      return;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int isTouch = digitalRead(VIB_SENSOR);
  if(isTouch == TOUCH)
 //serial.println(analogRead(VIB_SENSOR));
     Serial.println("TOUCH");
  //Serial.println(isTouch);
    AnalogMeasure = analogRead(VIB_SENSOR);
    Serial.println(AnalogMeasure);
    im.send_numdata(TAG_ID,AnalogMeasure);
  
    
  
  delay(100);
}
