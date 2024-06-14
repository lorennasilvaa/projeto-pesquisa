const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;
const long distanciaLimite = 10; // Distância em cm

unsigned long ultimoTempo = 0;  // Armazena o último tempo em que o LED piscou
const long intervalo = 10;         // Intervalo de tempo em milissegundos (0.5 segundos)
bool estadoLed = LOW;               // Estado atual do LED

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duracao, distancia;
  unsigned long tempoAtual = millis();

  // Envia um pulso de 10us para o pino Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lê o tempo de retorno do pulso no pino Echo
  duracao = pulseIn(echoPin, HIGH);

  // Calcula a distância (duração / 2 porque o pulso vai e volta,
  // e / 29.1 para converter de microsegundos para cm)
  distancia = duracao / 29.1 / 2;

  // Imprime a distância no monitor serial
  Serial.print("Distance: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Verifica se a distância é menor que 10 cm
  if (distancia < distanciaLimite) {
    // Verifica se o intervalo passou
    if (tempoAtual - ultimoTempo >= intervalo) {
      // Salva o tempo da última mudança
      ultimoTempo = tempoAtual;

      // Inverte o estado do LED
      estadoLed = !estadoLed;
      digitalWrite(ledPin, estadoLed);
    }
  } else {
    // Garante que o LED esteja desligado se a distância for maior ou igual a 10 cm
    digitalWrite(ledPin, LOW);
    estadoLed = LOW;
  }

  delay(100); // Pequeno atraso para estabilidade
}
