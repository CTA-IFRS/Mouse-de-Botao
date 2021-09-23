#include <Mouse.h>


/*
  ButtonMouseControl

  Para placas de arduino micro, Leonardo and Due boards only.

  Controla o mouse a partir de cinco botões.

  Hardware:
  - cinco botões de pressão conectados a D2, D3, D4, D5, D6

  O movimento do mouse é sempre relativo. Este Sketch lê quatro botões,
  e os usa para definir o movimento do mouse.

  AVISO: Quando você usa o comando Mouse.move (), o Arduino assume o controle do movimento do mouse!

  criado em 15 de março de 2012
  modificado 27 mar 2012
  por Tom Igoe

  Este código de exemplo está no domínio público.
  http://www.arduino.cc/en/Tutorial/ButtonMouseControl
*/



#define DEBOUNCING 50     //tempo(millisegundos) para o DEBOUNCING
#define TEMPO 800         //tempo para fazer a funcao de acelerar o mouse(valor em milissegundos)
#define MULTIPLI 0.02     //Variar entre 0.001 e 0.08 para acelerar o avanco do mouse apos 800 milissegundos segurados
#define MULTIPLICA 8      //Velocidade maxima que o mouse tera no maximo do joystick(0-1023)

//dizendo ao programa o numero dos pinos conectados aos botões
const int analogico1 = A0;
const int analogico2 = A1;
const int StickButton = 10;

const int upButton = 3;
const int downButton = 2;
const int leftButton = 4;
const int rightButton = 5;

const int mouseButton = 6;
const int rightmouseButton = 7;
const int leftLong = 8;
const int doubleleft = 9;

int range = 3;              // multiplicador do movimento do mouse em X e Y, quanto maior o numero mais rapido fica o mouse
int responseDelay = 10;     // tempo de resposta do mouse(quanto maior o numero mais lento o mouse fica),numero em milisegundos
boolean variavel = 0, variavel2 = 1, variavel3 = 1, variavel4 = 1, variavel5 = 1;
int d = 0, a = 0;
float  t = 0.1;

void setup() {
  // inicializa as variaveis como entradas
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(mouseButton, INPUT_PULLUP);
  pinMode(leftLong, INPUT_PULLUP);
  pinMode(doubleleft, INPUT_PULLUP);
  pinMode(rightmouseButton, INPUT_PULLUP);
  // inicializa a biblioteca do mouse.h
  Mouse.begin();
  Serial.begin(9600);
}

void loop() {
  // Este loop é infinito,e em cada vez que o loop reinicia é feito a leitura dos botões
  int  xDistance = 0;
  int  yDistance = 0;

  boolean upState = !(digitalRead(upButton));
  boolean downState = !(digitalRead(downButton));
  boolean rightState = !(digitalRead(rightButton));
  boolean leftState = !(digitalRead(leftButton));

  if (((upState | downState | rightState | leftState) == 1) && d == 0) {
    a = millis();
    d = 1;
  }

  if (((upState | downState | rightState | leftState) == 0) && d == 1) {
    a = 0;
    d = 0;
  }

  if ((a + TEMPO) < (millis()) && d == 1) {
    t = t + MULTIPLI;
    xDistance = (leftState - rightState) * t;
    yDistance = (upState - downState) * t;
  } else {
    xDistance = (leftState - rightState) * range;
    yDistance = (upState - downState) * range;
    t = range;
  }
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }
  //se o botao esquerdo é apertado
  if (digitalRead(mouseButton) == LOW) {
    if (variavel2 == 1) {
      delay(DEBOUNCING);
      if (digitalRead(mouseButton) == LOW) {
        Mouse.press(MOUSE_LEFT);
        variavel2 = 0;
      }
    }
  } else {
    if (variavel2 == 0 && variavel5 == 0) {
      Mouse.release(MOUSE_LEFT);
      variavel2 = 1;
    }
  }

  // se o botao direito é apertado
  if (digitalRead(rightmouseButton) == LOW) {
    if (variavel3 == 1) {
      delay(DEBOUNCING);
      if (digitalRead(rightmouseButton) == LOW) {
        Mouse.press(MOUSE_RIGHT);
        variavel3 = 0;
      }
    }
  } else {
    Mouse.release(MOUSE_RIGHT);
    variavel3 = 1;
  }

  //se o botao de clique duplo é apertado
  if (digitalRead(doubleleft) == LOW) {
    if (variavel4 == 1) {
      delay(DEBOUNCING);
      if (digitalRead(doubleleft) == LOW) {
        // muda o estado lógico do botão
        if (!Mouse.isPressed(MOUSE_LEFT)) {
          Mouse.click(MOUSE_LEFT);
          delay(200);
          Mouse.click(MOUSE_LEFT);
          delay(500);
          variavel4 = 0;
        }
      }
    }
  } else {
    variavel4 = 1;
  }
  //se o botao de clique longo é apertado
  if (digitalRead(leftLong) == LOW) {
    if (digitalRead(leftLong) == LOW && variavel5 == 0) {
      // muda o estado lógico do botão
      if (variavel == 0) {
        Mouse.press(MOUSE_LEFT);
        Mouse.press(MOUSE_LEFT);
        delay(100);
        variavel5 = !variavel5;
        variavel = !variavel;
      } else {
        Mouse.release(MOUSE_LEFT);
        delay(100);
        variavel5 = !variavel5;
        variavel = !variavel;
      }
    }
  } else {
    variavel5 = 0;
  }
  delay(responseDelay);
}
