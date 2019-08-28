#include <Servo.h>
Servo srvq;
int angle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  srvq.attach(3);
}

static unsigned long tickStarted;
int motorSwing = 10;
void loop() {
  // put your main code here, to run repeatedly:
  
  for (angle=0; angle < 180; angle++){
    srvq.write(angle);
    delay(15);
  }

  for (angle=180; angle >0; angle--){
    srvq.write(angle);
    delay(15);
  }

  if (motorSwing < 10 ){
    motorSwing++;
    Serial.print("Swing: ");
    Serial.println(motorSwing);
  }else{
    long elapseTime = millis() - tickStarted;
    Serial.print(F("Elapse Time 10 Swing: "));
    Serial.println(elapseTime);

    Serial.print(F("Elapse Time per Swing: "));
    Serial.println(elapseTime/10);
    
    motorSwing = 0;
    tickStarted = millis();
  }
}
