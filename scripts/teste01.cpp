const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;
const long distanceThreshold = 10; // Distância em cm

unsigned long previousMillis = 0;  // Armazena o último tempo em que o LED piscou
const long interval = 500;         // Intervalo de tempo em milissegundos (0.5 segundos)
bool ledState = LOW;               // Estado atual do LED

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  unsigned long currentMillis = millis();

  // Envia um pulso de 10us para o pino Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lê o tempo de retorno do pulso no pino Echo
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distância (duração / 2 porque o pulso vai e volta,
  // e / 29.1 para converter de microsegundos para cm)
  distance = duration / 29.1 / 2;

  // Imprime a distância no monitor serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Verifica se a distância é menor que 10 cm
  if (distance < distanceThreshold) {
    // Verifica se o intervalo passou
    if (currentMillis - previousMillis >= interval) {
      // Salva o tempo da última mudança
      previousMillis = currentMillis;

      // Inverte o estado do LED
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  } else {
    // Garante que o LED esteja desligado se a distância for maior ou igual a 10 cm
    digitalWrite(ledPin, LOW);
    ledState = LOW;
  }

  delay(100); // Pequeno atraso para estabilidade
}
