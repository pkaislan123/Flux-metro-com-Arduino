
#include <LCD5110_Basic.h>

#define CLK  8
#define DIN  9
#define DC   10
#define RST  12
#define CE   11

#define button 4


int flowPin1 = 2;    //Este é o pino de entrada no Arduino
int flowPin2 = 3;    //Este é o pino de entrada no Arduino

double flowRate1;    //Este é o valor que pretende-se calcular
volatile int count1; //Este número precisa ser setado como volátil para garantir que ele seja atualizado corretamente durante o processo de interrupção
double flowRate2;    //Este é o valor que pretende-se calcular
volatile int count2; //Este número precisa ser setado como volátil para garantir que ele seja atualizado corretamente durante o processo de interrupção


boolean em_ciclo = false;

LCD5110 tela(CLK, DIN, DC, RST, CE);

//Obtendo as fontes
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup() {
  pinMode(flowPin1, INPUT); //Seta o pino de entrada
  pinMode(flowPin2, INPUT); //Seta o pino de entrada

  pinMode(button, INPUT_PULLUP); //Seta o pino como entrada pull up


  attachInterrupt(0, Flow1, RISING);  //Configura o interruptor 0 (pino 2 no Arduino Uno) para rodar a função "Flow"
  attachInterrupt(1, Flow2, FALLING);  //Configura o interruptor 0 (pino 3 no Arduino Uno) para rodar a função "Flow"

  Serial.begin(9600); //Inicia o Serial

  tela.InitLCD(); //Inicializando o display


  tela.setFont(SmallFont); //Definindo a fonte
  tela.print("Iniciando", LEFT, 0);
  delay(500);
  tela.print("Aguardando...", LEFT, 0);
  noInterrupts();
}
void loop() {

  if (!em_ciclo) {
    noInterrupts();

    if (digitalRead(button) == 0) {
      tela.clrScr();
      em_ciclo = true;
      delay(100);

    }


  } else {




    count1 = 0;      // Reseta o contador para iniciarmos a contagem em 0 novamente
    count2 = 0;
    interrupts();   //Habilita o interrupção no Arduino
    delay(1000);   //Espera 1 segundo
    noInterrupts(); //Desabilita o interrupção no Arduino


    //Cálculos matemáticos
    flowRate1 = (count1 * 2.25);        //Conta os pulsos no último segundo e multiplica por 2,25mL, que é a vazão de cada pulso
    flowRate1 = flowRate1 * 60;         //Converte segundos em minutos, tornando a unidade de medida mL/min
    flowRate1 = flowRate1 / 1000;       //Converte mL em litros, tornando a unidade de medida L/min

    flowRate2 = (count2 * 2.25);        //Conta os pulsos no último segundo e multiplica por 2,25mL, que é a vazão de cada pulso
    flowRate2 = flowRate2 * 60;         //Converte segundos em minutos, tornando a unidade de medida mL/min
    flowRate2 = flowRate2 / 1000;       //Converte mL em litros, tornando a unidade de medida L/min


    Serial.println(flowRate1);         //Imprime a variável flowRate no Serial
    Serial.println(flowRate2);         //Imprime a variável flowRate no Serial


    String Sfluxo1 = String(flowRate1);
    Sfluxo1.concat(" L/min");
    escreverNaTela("Fluxo 1:", 0, 0);
    escreverNaTela(Sfluxo1, 0, 10);
    flowRate1 = flowRate1 / 60;
    Sfluxo1 = String(flowRate1);
    Sfluxo1.concat(" L/seg");
    escreverNaTela(Sfluxo1, 0, 20);


    String Sfluxo2 = String(flowRate2);
    Sfluxo2.concat(" L/min");
    escreverNaTela("Fluxo 2:", 0, 30);
    escreverNaTela(Sfluxo2, 0, 35);
    flowRate2 = flowRate2 / 60;
    Sfluxo2 = String(flowRate2);
    Sfluxo2.concat(" L/seg");
    escreverNaTela(Sfluxo2, 0, 40);

    if (digitalRead(button) == 0) {
      noInterrupts();
      tela.clrScr();
      tela.print("Solte...", LEFT, 0);
      while (digitalRead(button) == 0);
      tela.clrScr();
      tela.print("Aguardando...", LEFT, 0);
      em_ciclo = false;
      return;
    }


  }



}

void escreverNaTela(String texto, int coluna, int linha) {
  tela.print(texto, coluna, linha);
}

void Flow1()
{
  count1++; //Quando essa função é chamada, soma-se 1 a variável "count1"
}

void Flow2()
{
  count2++; //Quando essa função é chamada, soma-se 1 a variável "count2"
}
