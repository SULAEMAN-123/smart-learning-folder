#define LIGHT A3
#define LED 9
#define BUZZER 6


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LIGHT,INPUT);
pinMode(LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

int value = analogRead(LIGHT);
int data= map (value,0,1023,1023,0);


Serial.print("LIGHT : ");
Serial.println(data);

analogWrite(LED,value);
delay(100);

if (data < 800) {
tone(BUZZER,400);
delay(100);
noTone(BUZZER);
delay(100);
}
else {
  delay(500);
}}
