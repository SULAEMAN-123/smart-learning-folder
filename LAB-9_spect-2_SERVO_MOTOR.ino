#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <Servo.h>

Servo srvq;
int angle = 0;

//#define LIGHT A3
//#define LED 9
//#define BUZZER 6
//#define SIGNAL_PIN A0

IoTMakers im;

#define deviceID    "k19740D1566958971888"
#define authRqtNo   "6a8rwovq7"
#define extrSysID   "OPEN_TCP_001PTL001_1000007623"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2
#define TAG_ID "SERVO"

int distance=0;

void setup() {
  // put your setup code here, to run once:
  initIoTMakers();
   Serial.begin(9600);
  srvq.attach(3);
  
}

void initIoTMakers(){
  while (1){
    Serial.print(F("Connecting to AP . . ."));

    while (im.begin(WIFI_SSID, WIFI_PASS) <0 ) {
      Serial.println(F("Retrying..."));
      delay (100);
    }

    Serial.println("Success");
    im.init(deviceID, authRqtNo, extrSysID);
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

static unsigned long tickStarted;

void loop() {
  angle = angle > 180 ? 0 : angle+1;
  srvq.write(angle);
  delay(15);
  
  if ((millis() - tickStarted) >= 500){
    Serial.println(angle);
    im.send_numdata(TAG_ID, angle);
    tickStarted = millis();
  }
}
