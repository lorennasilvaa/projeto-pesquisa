const int ledPin = 13;
long tempoAnterior = 0;

long intervaloTempo = 1000; //1s

bool statusLed = LOW;

void setup(){
  pinMode(ledPin, OUTPUT);
}

void loop(){
  unsigned long tempoAtual = millis();

  if(tempoAtual - tempoAnterior >= intervaloTempo){
    tempoAnterior = tempoAtual;
    statusLed = !statusLed;
    digitalWrite(ledPin, statusLed); 
  }
}
