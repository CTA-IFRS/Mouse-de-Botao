#include <Mouse.h>
#include <Keyboard.h> 

/*
  ================================================================================
  Controle Avançado de Mouse e Teclado (v6.2 - Correção Direção Teclado)
  ================================================================================
  - Corrigida a atribuição dos pinos direcionais para o Modo Teclado.
  --------------------------------------------------------------------------------
*/

// --- Pinos dos botões (DIRECIONAIS CORRIGIDOS) ---
const int upButton = 9;
const int downButton = 8;
const int leftButton = 15;
const int rightButton = 10;
// --- Pinos de Ação ---
const int mouseButton = 7;
const int rightmouseButton = 3;
const int leftLong = 4;
const int doubleleft = 2;
const int keyboardModeButton = 6;
const int scrollButton = 5;

// --- Constantes de configuração ---
#define DEBOUNCING 50
#define TEMPO 400
#define MULTIPLI 0.1

// --- Variáveis de controle de estado ---
int range = 1;
int responseDelay = 10;
boolean variavel = 0, variavel2 = 1, variavel3 = 1, variavel4 = 1, variavel5 = 1;
int d = 0, a = 0;
float t = 0.1;

// --- Variáveis para os modos especiais ---
bool scrollMode = false;
bool keyboardMode = false;
int lastScrollButtonState = HIGH;
int lastKeyboardModeButtonState = HIGH;

// --- Variáveis para rastrear o estado das teclas pressionadas ---
bool upArrowPressed = false;
bool downArrowPressed = false;
bool leftArrowPressed = false;
bool rightArrowPressed = false;


// ================================================================================
//  FUNÇÃO SETUP
// ================================================================================
void setup() {
  // Inicializa os pinos
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(mouseButton, INPUT_PULLUP);
  pinMode(leftLong, INPUT_PULLUP);
  pinMode(doubleleft, INPUT_PULLUP);
  pinMode(rightmouseButton, INPUT_PULLUP);
  pinMode(scrollButton, INPUT_PULLUP);
  pinMode(keyboardModeButton, INPUT_PULLUP);

  Mouse.begin();
  Keyboard.begin(); 
}

// ================================================================================
//  FUNÇÃO LOOP
// ================================================================================
void loop() {
  // --- Leitura do estado de todos os botões ---
  boolean upState = !(digitalRead(upButton));
  boolean downState = !(digitalRead(downButton));
  boolean rightState = !(digitalRead(rightButton));
  boolean leftState = !(digitalRead(leftButton));
  boolean mouseLeftState = (digitalRead(mouseButton) == LOW);
  boolean mouseRightState = (digitalRead(rightmouseButton) == LOW);
  boolean doubleLeftState = (digitalRead(doubleleft) == LOW);
  boolean leftLongState = (digitalRead(leftLong) == LOW);
  
  int currentScrollButtonState = digitalRead(scrollButton);
  int currentKeyboardModeButtonState = digitalRead(keyboardModeButton);

  // --- Lógica para gerenciar os MODOS (Scroll e Teclado) ---
  if (currentScrollButtonState == LOW && lastScrollButtonState == HIGH) {
    if (keyboardMode) {
      Keyboard.releaseAll();
      keyboardMode = false;
    }
    scrollMode = !scrollMode;
    delay(DEBOUNCING);
  }

  if (currentKeyboardModeButtonState == LOW && lastKeyboardModeButtonState == HIGH) {
    if (scrollMode) {
      scrollMode = false;
    }
    keyboardMode = !keyboardMode;
    if (!keyboardMode) {
      Keyboard.releaseAll();
    }
    delay(DEBOUNCING);
  }

  lastScrollButtonState = currentScrollButtonState;
  lastKeyboardModeButtonState = currentKeyboardModeButtonState;

  bool anyActionButtonPressed = mouseLeftState || mouseRightState || doubleLeftState || leftLongState;
  if (anyActionButtonPressed) {
    if (scrollMode) scrollMode = false;
    if (keyboardMode) {
      Keyboard.releaseAll();
      keyboardMode = false;
    }
  }

  // --- Execução das Ações Baseado no Modo Atual ---
  if (scrollMode) {
    // --- MODO SCROLL ATIVADO ---
    int scrollAmount = 0;
    if (upState) scrollAmount = 1;
    if (downState) scrollAmount = -1;
    
    if (scrollAmount != 0) {
      Mouse.move(0, 0, scrollAmount);
    }

  } else if (keyboardMode) {
    // ***** MODO TECLADO ATIVADO *****
    // Seta para Cima
    if (upState && !upArrowPressed) {
      Keyboard.press(KEY_UP_ARROW);
      upArrowPressed = true;
    } else if (!upState && upArrowPressed) {
      Keyboard.release(KEY_UP_ARROW);
      upArrowPressed = false;
    }
    // Seta para Baixo
    if (downState && !downArrowPressed) {
      Keyboard.press(KEY_DOWN_ARROW);
      downArrowPressed = true;
    } else if (!downState && downArrowPressed) {
      Keyboard.release(KEY_DOWN_ARROW);
      downArrowPressed = false;
    }
    // Seta para Esquerda
    if (leftState && !leftArrowPressed) {
      Keyboard.press(KEY_LEFT_ARROW);
      leftArrowPressed = true;
    } else if (!leftState && leftArrowPressed) {
      Keyboard.release(KEY_LEFT_ARROW);
      leftArrowPressed = false;
    }
    // Seta para Direita
    if (rightState && !rightArrowPressed) {
      Keyboard.press(KEY_RIGHT_ARROW);
      rightArrowPressed = true;
    } else if (!rightState && rightArrowPressed) {
      Keyboard.release(KEY_RIGHT_ARROW);
      rightArrowPressed = false;
    }
    
  } else {
    // --- MODO NORMAL (MOUSE) ---
    int xDistance = 0;
    int yDistance = 0;

    // Lógica de aceleração do cursor
    if (((upState | downState | rightState | leftState) == 1) && d == 0) { a = millis(); d = 1; }
    if (((upState | downState | rightState | leftState) == 0) && d == 1) { a = 0; d = 0; }

    float currentSpeed;
    if ((a + TEMPO) < (millis()) && d == 1) {
      t = t + MULTIPLI;
      currentSpeed = t;
    } else {
      t = range;
      currentSpeed = range;
    }

    xDistance = (rightState - leftState) * currentSpeed;
    yDistance = (downState - upState) * currentSpeed;
    
    if ((xDistance != 0) || (yDistance != 0)) {
      Mouse.move(xDistance, yDistance, 0);
    }

    // Ações de clique
    if (mouseLeftState) {
      if (variavel2 == 1) {
        delay(DEBOUNCING);
        if (digitalRead(mouseButton) == LOW) { Mouse.press(MOUSE_LEFT); variavel2 = 0; }
      }
    } else {
      if (variavel2 == 0 && variavel5 == 0) { Mouse.release(MOUSE_LEFT); variavel2 = 1; }
    }
    if (mouseRightState) {
      if (variavel3 == 1) {
        delay(DEBOUNCING);
        if (digitalRead(rightmouseButton) == LOW) { Mouse.press(MOUSE_RIGHT); variavel3 = 0; }
      }
    } else {
      Mouse.release(MOUSE_RIGHT); variavel3 = 1;
    }
    if (doubleLeftState) {
      if (variavel4 == 1) {
        delay(DEBOUNCING);
        if (digitalRead(doubleleft) == LOW) {
          if (!Mouse.isPressed(MOUSE_LEFT)) { Mouse.click(MOUSE_LEFT); delay(100); Mouse.click(MOUSE_LEFT); variavel4 = 0; }
        }
      }
    } else {
      variavel4 = 1;
    }
    if (leftLongState) {
      if (digitalRead(leftLong) == LOW && variavel5 == 0) {
        if (variavel == 0) { Mouse.press(MOUSE_LEFT); delay(100); }
        else { Mouse.release(MOUSE_LEFT); delay(100); }
        variavel5 = !variavel5; variavel = !variavel;
      }
    } else {
      variavel5 = 0;
    }
  }
  
  delay(responseDelay);
}
