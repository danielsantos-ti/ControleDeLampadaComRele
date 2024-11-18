/*
  Controle Simples de um LED com Arduino, Relé e Pushbutton

  Descrição:
  Este programa permite controlar uma LED através de um botão e um módulo relé. 
  Cada vez que o botão é pressionado, o estado do relé muda, ligando ou desligando 
  a LED. O programa usa a função INPUT_PULLUP para simplificar a leitura do botão, 
  evitando a necessidade de resistores externos.

  Funcionamento:
  - Quando o botão é pressionado, o estado do relé é invertido:
      - Se o relé estiver desligado, ele será ligado, acendendo a LED.
      - Se o relé estiver ligado, ele será desligado, apagando a LED.
  - Um pequeno atraso (debounce) é incluído para evitar leituras duplicadas do botão.

  Conexões:
  - Botão: Conectado ao pino 2 (D2) e ao GND do Arduino.
  - Relé: Conectado ao pino 4 (D4) do Arduino, ao GND e ao 5V do Arduino.
  - LED: Conectada ao relé nos terminais COM (comum) e NO (normalmente aberto).

  Atenção:
  - Para acionar cargas como LED'S, sempre tome cuidado com a fiação e 
    use relés com capacidade suficiente para suportar a carga.
  - Esse programa é ideal para projetos de demonstração e aprendizado. 
    Para aplicações de alta potência, consulte recomendações de segurança elétrica.

  Autor: Daniel Santos
  Data: 07/11/2024
  Local: GDE - Ilhéus
*/


//Define os pinos do botão e do relé
const int buttonPin = 2;
const int relePin = 7;
const int sensorPin = A0; // Pino analógico para o sensor ACS712

//Define o estado do relé como desligado
bool estadoDoRele = false;


void setup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, LOW);
  Serial.begin(9600);

}

void loop() {
  
  //Variável armazena o status do botão(pressionado ou não pressionado)
  int estadoDoBotao = digitalRead(buttonPin);

  //Verifica se o botão foi pressionado
  if(estadoDoBotao == LOW){
      
      estadoDoRele = !estadoDoRele; //Inverte o estado do relé
      digitalWrite(relePin, estadoDoRele); //Atualiza o estado do relé
      delay(300); //AtraSo para evitar reboots do botão

  }

  // Lê o valor do sensor de corrente ACS712
  float valorDoAcs = 0.0;
  float amostras = 0.0;

  // Número de amostras para obter uma média
  int numeroDeAmostras = 150;

  for(int i = 0; i < numeroDeAmostras; i++){

    // Lê o valor do sensor
    valorDoAcs = analogRead(sensorPin);

    // Armazena o somatório dos valores das amostras
    amostras += valorDoAcs;
    
    // Atraso para estabilizar o ADC
    delay(5);
  }

  // Calcula a média das amostras
  float mediaDoAcs = amostras / numeroDeAmostras;  

  // Converte a leitura média para corrente (em amperes)
  // Fórmula dada no documento do ACS712
  float corrente = (2.5 - (mediaDoAcs * (5.0 / 1024.0))) / 0.066;

  // Exibe o valor da corrente no monitor serial
  Serial.print("Corrente: ");
  Serial.print(corrente);
  Serial.println(" A");

  // Atraso entre leitura de corrente
  delay(500); 

}
