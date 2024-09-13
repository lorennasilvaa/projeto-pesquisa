/*
O CIRCUITO CONTÉM: UM ARDUINO NANO, UM MOTOR DE VIBRAÇÃO E UM SENSOR ULTRASSÔNICO
  * O SENSOR ULTRASSÔNICO É UTILIZADO PARA ENTRADA DE DADOS
  * O MOTOR DE VIBRAÇÃO É UTILIZADO PARA SAÍDA DE DADOS
  * SE UM OBJETO ESTIVER A UMA DISTÂNCIA MENOR QUE A DETERMINADA, O MOTOR DEVE VIBRAR DE FORMA INVERSAMENTE PROPORCIONAL À DISTÂNCIA VERIFICADA
*/

/*
      COISAS QUE PODEM DAR ERRADO:
      * Tô usando 0 e 1 ao invés de HIGH e LOW
*/


//CONSTANTES UTILIZADAS
const int motorVibracao = 12; //variavel que controla o motor de vibracao
const int pinoEcho = 10; //variavel que controla o pino echo do sensor ultrassônico (emite a onda)
const int pinoTrig = 9; //variavel que controla o pino trig do sensor ultrasônico (recebe a onda)

void setup() {
  Serial.begin(9600);

  //configurando saídas e entradas de dados
  pinMode(motorVibracao, OUTPUT); 
  pinMode(pinoEcho, INPUT);
  pinMode(pinoTrig, OUTPUT);

  inicializarSistema(); 
}


void loop() {
  Serial.println(calcularDistancia());
  verificarDistancia(calcularDistancia());
}



//FUNÇÃO RESPONSÁVEL POR INICIALIAZAR AS VARIÁVEIS COM VALORES PADRÃO E TESTAR O MOTOR DE VIBRAÇÃO
void inicializarSistema() { 
  //vibra o motor durante um segundo, quando o codigo é executado
  digitalWrite(motorVibracao, 1);
  delay(1000);
  digitalWrite(motorVibracao, 0);

  //testa se o sensor ultrassônico está recebendo os sinais
  long duracao;
  int distancia;
  
  digitalWrite(pinoTrig, 0);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, 1);
  delayMicroseconds(10);
  
  duracao = pulseIn(pinoEcho, 1); //lê a duracao do pulso (quanto tempo o Echo fica em estado HIGH)
  distancia = (duracao / 2) * 0.034; //calcula a distância em centímetros do objeto verificado

  //APENAS PARA TESTES
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(500);
}


// FUNÇAO RESPONSÁVEL POR VERIFICAR E RETORNAR A DISTANCIA
int calcularDistancia(){
  digitalWrite(pinoTrig, 0);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, 1);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, 0);

  long duracao = pulseIn(pinoEcho, 1); //lê o tempo que o pulso levou para retornar

  int distancia = (duracao / 2.0) * 0.0343;

  // Imprime a distância no monitor serial
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(500); // Aguarda meio segundo antes da próxima medição
  return distancia;
}


void verificarDistancia(int dist){
  dist = calcularDistancia();
  int distLimite = 10;
  
  if(dist < distLimite){
    digitalWrite(motorVibracao, 1);
    delay(100);
    digitalWrite(motorVibracao, 0); 
  }
}

