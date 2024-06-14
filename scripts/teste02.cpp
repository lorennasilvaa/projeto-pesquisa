const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float avgDistance = getAverageDistance();
  
  int blinkDelay = calculateBlinkDelay(avgDistance);
  
  digitalWrite(ledPin, HIGH);
  delay(blinkDelay);
  digitalWrite(ledPin, LOW);
  delay(blinkDelay);
  
  Serial.print("Distance: ");
  Serial.print(avgDistance);
  Serial.print(" cm");
  Serial.print(", Blink delay: ");
  Serial.print(blinkDelay);
  Serial.println(" ms");
}

float getAverageDistance() {
  float totalDistance = 0;
  for (int i = 0; i < 10; i++) {
    totalDistance += measureDistance();
    delay(50);  // Pequeno atraso entre as medições
  }
  return totalDistance / 10;
}

float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  
  return distance;
}

int calculateBlinkDelay(float distance) {
  int delayTime = 1000; // Default to 1 second
  
  if (distance > 0) {
    delayTime = 5000 / distance;
  }
  
  // Garantir que o delay não seja menor que um valor mínimo (por exemplo, 50 ms)
  if (delayTime < 50) {
    delayTime = 50;
  }
  
  return delayTime;
}
