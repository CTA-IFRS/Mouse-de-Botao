#include <Mouse.h>
#include <Keyboard.h>

/*
  Mouse de botoes com funcionalidade: movimento do cursor, clique, clique duplo, clique preso, clique direito, scroll bidirecional e ajuste de velocidade (cursor e scroll)
  Para placas de arduino micro, Leonardo, Pro Micro and Due boards only.
  O movimento do mouse é sempre relativo. 
  
  Código de exemplo criado originalmente por Tom Igoe e modificado por bolsistas do projeto CRTA.
  
*/

#define DEBOUNCING 50          //tempo(millisegundos) para o DEBOUNCING
#define TEMPO 200              //tempo para fazer a funcao de acelerar o mouse(valor em milissegundos)
#define MULTIPLI 0.08          //Variar entre 0.001 e 0.08 para acelerar o avanco do mouse apos 800 milissegundos segurados
#define MULTIPLICA 1023        //Velocidade maxima que o mouse tera no maximo do joystick(0-1023)
#define SCROLL_SPEED_LOW 1     //Velocidade scroll lento
#define SCROLL_SPEED_MEDIUM 2  //Velocidade scroll medio
#define SCROLL_SPEED_HIGH 5    //Velocidade scroll rapido

// Pinos dos botões
const int upButton = 2;             //movimento acima 
const int downButton = 3;           //movimento abaixo
const int leftButton = 5;          //movimento esquerda
const int rightButton = 4;         //movimento direito
const int mouseButton = 6;         //clique esquerdo
const int rightmouseButton = 7;    //clique direito
const int leftLong = 8;            //clique esquerdo preso
const int doubleleft = 9;           //clique esquerdo duplo
const int ScrollButton = 10;        //botao scrool
const int velocidade = 11;          //botao para alternar velocidade de movimento e scroll

int range = 1;              // multiplicador do movimento do mouse em X e Y, quanto maior o numero mais rapido fica o mouse
int responseDelay = 10;     // tempo de resposta do mouse(quanto maior o numero mais lento o mouse fica),numero em milisegundos
boolean variavel = 0, variavel2 = 1, variavel3 = 1, variavel4 = 1, variavel5 = 1, variavel6 = 1;
int d = 0;
unsigned long espaco = 0, a = 0;
float t = 0.1;
boolean scrollMode = false;
int scrollSpeed = SCROLL_SPEED_LOW;
int scrollSpeedLevel = 0; // 0 = baixo, 1 = médio, 2 = alto

void setup() {
  // inicializa as variaveis como entradas

  // Para utilizar os modulos analogicos, descomentar esta secao
  //pinMode(analogico1, INPUT);
  //pinMode(analogico2, INPUT);
  
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(mouseButton, INPUT_PULLUP);
  pinMode(leftLong, INPUT_PULLUP);
  pinMode(doubleleft, INPUT_PULLUP);
  pinMode(rightmouseButton, INPUT_PULLUP);
  pinMode(ScrollButton, INPUT_PULLUP);
  pinMode(velocidade, INPUT_PULLUP);

  // inicializa bibliotecas
  Mouse.begin();
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  // Este loop e infinito, cada vez que o loop reinicia e feito a leitura dos botoes
  
  int xDistance = 0;
  int yDistance = 0;

  boolean upState = !digitalRead(upButton);
  boolean downState = !digitalRead(downButton);
  boolean rightState = !digitalRead(rightButton);
  boolean leftState = !digitalRead(leftButton);

  // Controle do modo de scroll
  if (digitalRead(ScrollButton) == LOW) {
    if (variavel6 == 1) {
      delay(DEBOUNCING);
      if (digitalRead(ScrollButton) == LOW) {
        scrollMode = !scrollMode; // Alterna entre modo normal e modo de scroll
        variavel6 = 0;
      }
    }
  } else {
    variavel6 = 1;
  }

  // Controle da velocidade de scroll e movimento
  if ((digitalRead(velocidade) == LOW) && (espaco + 1000) < millis()) {
    espaco = millis();
    scrollSpeedLevel = (scrollSpeedLevel + 1) % 3;
    switch (scrollSpeedLevel) {
      case 0:
        scrollSpeed = SCROLL_SPEED_LOW;
        range = 1;
        break;
      case 1:
        scrollSpeed = SCROLL_SPEED_MEDIUM;
        range = 2;
        break;
      case 2:
        scrollSpeed = SCROLL_SPEED_HIGH;
        range = 5;
        break;
    }
    Serial.print("Scroll/Move Speed: ");
    Serial.println(scrollSpeed);
  }

  if (scrollMode) {
    // Modo de scroll bidirecional
    int scrollY = (upState - downState) * scrollSpeed;
    int scrollX = (leftState - rightState) * scrollSpeed;

    if (scrollY != 0) {
      Mouse.move(0, 0, scrollY);
    }

    if (scrollX != 0) {
      // Simula o scroll horizontal
      Keyboard.press(KEY_LEFT_SHIFT);
      Mouse.move(0, 0, scrollX);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
  } else {
    // Modo de movimento normal do mouse
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
      xDistance = (rightState - leftState) * t;
      yDistance = (downState - upState) * t;
    } else {
      xDistance = (rightState - leftState) * range;
      yDistance = (downState - upState) * range;
      t = range;
    }
    if ((xDistance != 0) || (yDistance != 0)) {
      Mouse.move(xDistance, yDistance, 0);
    }
  }

  // Controle do botão esquerdo do mouse
  if (digitalRead(mouseButton) == LOW) {
    if (variavel2 == 1) {
      delay(DEBOUNCING);
      if (digitalRead(mouseButton) == LOW) {
        Mouse.press(MOUSE_LEFT);
        variavel2 = 0;
      }
    }
  } else {
    if (variavel2 == 0) {
      Mouse.release(MOUSE_LEFT);
      variavel2 = 1;
    }
  }

  // Controle do botão direito do mouse
  if (digitalRead(rightmouseButton) == LOW) {
    if (variavel3 == 1) {
      delay(DEBOUNCING);
      if (digitalRead(rightmouseButton) == LOW) {
        Mouse.press(MOUSE_RIGHT);
        variavel3 = 0;
      }
    }
  } else {
    if (variavel3 == 0) {
      Mouse.release(MOUSE_RIGHT);
      variavel3 = 1;
    }
  }

  // Controle de duplo clique esquerdo
  if (digitalRead(doubleleft) == LOW) {
    if (variavel4 == 1) {
      delay(DEBOUNCING);
      if (digitalRead(doubleleft) == LOW) {
        Mouse.click(MOUSE_LEFT);
        delay(100);
        Mouse.click(MOUSE_LEFT);
        variavel4 = 0;
      }
    }
  } else {
    variavel4 = 1;
  }

  //se o botao de clique esquerdo preso e apertado
  if (digitalRead(leftLong) == LOW) {
    delay(DEBOUNCING);
    if (digitalRead(leftLong) == LOW && variavel == 1) {
      // muda o estado l?gico do bot?o
      Mouse.press(MOUSE_LEFT);
      variavel = !variavel;
      variavel5 = !variavel5;
    }
  } else {
    variavel = 1;

  }
  if (variavel2 == 0 || variavel6 == 0) {
    variavel5 = 1;
  }
  if (variavel2 == 1 && variavel5 == 1 && variavel6 == 1) {
    Mouse.release(MOUSE_LEFT);
  }

  delay(responseDelay);
}
