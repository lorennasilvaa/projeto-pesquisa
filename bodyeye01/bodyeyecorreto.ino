/*
O CIRCUITO CONTÉM: UM ARDUINO NANO, UM MOTOR DE VIBRAÇÃO E UM SENSOR ULTRASSÔNICO
  * O SENSOR ULTRASSÔNICO É UTILIZADO PARA ENTRADA DE DADOS
  * O MOTOR DE VIBRAÇÃO É UTILIZADO PARA SAÍDA DE DADOS
  * SE UM OBJETO ESTIVER A UMA DISTÂNCIA MENOR QUE A DETERMINADA, O MOTOR DEVE VIBRAR ENQUANTO O OBJETO ESTIVER SENDO DETECTADO. 
*/

//CONSTANTES UTILIZADAS
const int motorVibracao = 12; //variavel que controla o motor de vibracao
const int pinoEcho = 4; //variavel que controla o pino echo do sensor ultrassônico (emite a onda)
const int pinoTrig = 5; //variavel que controla o pino trig do sensor ultrasônico (recebe a onda)

//FUNCAO SETUP (EXECUTADA TODA VEZ QUE SE REINICIA O ARDUINO)
void setup() {
  Serial.begin(9600); //ativa monitor serial para analise de dados
 
  //configurando saídas e entradas de dados
  pinMode(motorVibracao, OUTPUT); 
  pinMode(pinoEcho, INPUT);
  pinMode(pinoTrig, OUTPUT);

  inicializarSistema(); //chama a funcao inicializarSistema()
}

//FUNCAO LOOP (EXECUTADA CONTINUAMENTE)
void loop() {
  Serial.println(calcularDistancia()); //mostra a distancia calculada pelo sensor ultrassonico no monitor serial
  verificarDistancia(calcularDistancia()); //chama a funcao verificarDistancia() e passa por parametro a saida da funcao calcularDistancia() 
}

//FUNÇÃO RESPONSÁVEL POR INICIALIAZAR AS VARIÁVEIS COM VALORES PADRÃO E TESTAR O MOTOR DE VIBRAÇÃO
void inicializarSistema() { 
  //vibra o motor durante um segundo quando o codigo é executado
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

  //SAIDA NO MONITOR SERIAL (APENAS PARA TESTES)
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
  delayMicroseconds(7);
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
  int distLimite = 10; //configura a distancia limite para 10cm
  
  if(dist < distLimite){
    digitalWrite(motorVibracao, 1);
    delay(10);
    verificarDistancia(calcularDistancia());
  } else {
    digitalWrite(motorVibracao, 0);
    loop(); //chama a funcao loop para reiniciar a verificacao de distancia 
  }
}
