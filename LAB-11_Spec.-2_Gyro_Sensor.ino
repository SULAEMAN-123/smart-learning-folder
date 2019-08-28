#include<Wire.h>
#include <IoTStarterKit_WiFi.h>


#define VIB_SENSOR A0
#define TOUCH 1

IoTMakers im;

#define deviceID    "k19740D1566973718537"
#define authnRqtNo  "dmi0biqkk"
#define extrSysID   "OPEN_TCP_001PTL001_1000007623"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2
#define TAG_ID "GYRO"

int AnalogMeasure;


const int MPU = 0x68;  // I2C address of MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
 
void setup() {

  initIoTMakers();
  
  Serial.begin(9600);
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
 
  // gyro scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0xF8);
  Wire.endTransmission(true);
 
  // acc scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0xF8);
  Wire.endTransmission(true);

  
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
    }}}

    
void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  
  AcX = Wire.read() << 8 | Wire.read();  // ACCEL_X
  AcY = Wire.read() << 8 | Wire.read();  // ACCEL_Y
  AcZ = Wire.read() << 8 | Wire.read();  // ACCEL_Z
  Tmp = Wire.read() << 8 | Wire.read();  // Temperature
  GyX = Wire.read() << 8 | Wire.read();  // GYRO_X
  GyY = Wire.read() << 8 | Wire.read();  // GYRO_Y
  GyZ = Wire.read() << 8 | Wire.read();  // GYRO_Z
 
  int xAxis = (AcX - 1090);
  int yAxis = (AcY - 930);
  int zAxis = (AcZ - 1000);

  Serial.print("Gyro (x, y, z): ");
  Serial.print(xAxis);
  Serial.print(" ");
  Serial.print(yAxis);
  Serial.print(" ");
  Serial.print(zAxis);
  Serial.println(" ");

  float tempC = (float) Tmp/340+36.53;
  Serial.print("Temperature: ");
  Serial.println(tempC);

  im.send_numdata(TAG_ID,tempC);
  
  delay(250);
}
