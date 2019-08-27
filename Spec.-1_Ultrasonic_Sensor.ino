#define trigPin 13    
#define echoPin 12
#define BUZZER 6


 
void setup()
{
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

//pulsing(pin, pulse);

void loop()
{
  double duration, distance; 
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
   
  digitalWrite(trigPin, LOW); 
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration *17/1000;

  if (distance >= 200 || distance <=0 ) {
  Serial.println("unable to measure the distance");
    
  }
  else {
    
  Serial.print(distance);
  Serial.println("cm"); 
}

if (distance <=30) {
  tone(BUZZER,600);
  delay(distance * 10);
  noTone(BUZZER);
  delay(distance*10);
}
else {
delay(500);
}
}
