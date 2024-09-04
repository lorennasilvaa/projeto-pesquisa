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

const int motorVibracao = 11; //variavel que controla o motor de vibracao
const int pinoEcho = 8; //variavel que controla o pino echo do sensor ultrassônico (emite a onda)
const int pinoTrig = 7; //variavel que controla o pino trig do sensor ultrasônico (recebe a onda)


void setup() {
  Serial.begin(9600);
  
  pinMode(motorVibracao, OUTPUT);
  pinMode(pinoEcho, INPUT);
  pinMode(pinoTrig, OUTPUT);

  inicializarSistema(); 
}

void loop() {
  

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

  //envia um pulso de 10 microsegundos no pino Trig
  digitalWrite(pinoTrig, 0);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, 1);
  delayMicroseconds(10);

  //lê a duracao do pulso (quanto tempo o Echo fica em estado HIGH)
  duracao = pulseIn(pinoEcho, 1);

  //calcula a distância em centímetros do objeto verificado
  distancia = duracao * 0.034 / 2;

  //APENAS PARA TESTES
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(500);
}
