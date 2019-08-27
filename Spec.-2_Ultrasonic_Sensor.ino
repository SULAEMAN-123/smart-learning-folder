#define trigPin 9    
#define echoPin 8
#define BUZZER 6

int redPin   = 13;
int greenPin = 12;
int bluePin  = 11;

 
void setup()
{
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
 pinMode(redPin, OUTPUT);
 pinMode(greenPin, OUTPUT);
 pinMode(bluePin, OUTPUT);
}

//pulsing(pin, pulse);
void setColor(int red, int green, int blue){
 analogWrite(redPin,255-red);
 analogWrite(greenPin,255-green);
 analogWrite(bluePin,255-blue);

 
}

void loop()
{

long duration, distance; 
  
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

if (distance <=20) {
  
 // analogWrite(redPin,distance);
  tone(BUZZER,600);
  delay(distance * 10);
  noTone(BUZZER);
  delay(distance*10);
}
else {
delay(500);
}
//}
 if (distance>50){
 
      setColor(0, 0, 255);
    }else if (distance > 20){
      setColor(0, 255, 0);
    }else{
      setColor(255, 0, 0);
    }
    
}
