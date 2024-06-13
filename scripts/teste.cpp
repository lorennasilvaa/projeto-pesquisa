const int pinVibracao = 7;
unsigned long tempoAnterior = 0;
const long intervalo = 500;

void setup()
{
  pinMode(pinVibracao, OUTPUT);
}

void loop()
{
  unsigned long tempoAtual = millis();
  
  if(tempoAtual - tempoAnterior >= intervalo){
    tempoAnterior = tempoAtual;
    int estadoVibracao = digitalRead(pinVibracao);
    digitalWrite(pinVibracao, !estadoVibracao);
  }
}