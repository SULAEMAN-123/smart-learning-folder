#define VIB_SENSOR A0
#define TOUCH 1

int AnalogMeasure;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VIB_SENSOR, INPUT);
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
  
  delay(100);
}
