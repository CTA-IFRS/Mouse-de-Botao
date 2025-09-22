#include <Mouse.h>
#include <Keyboard.h> 

/*
  ================================================================================
  Controle Avançado de Mouse e Teclado (v6.3 - Versão Final Estável)
  ================================================================================

  Descrição Geral:
  Este código transforma um Arduino com capacidade USB nativa em um dispositivo
  híbrido de mouse e teclado, controlado por botões. O dispositivo possui três
  modos de operação principais: Modo Mouse (padrão), Modo Scroll e Modo Teclado,
  permitindo diferentes formas de interação com o computador.

  Compatibilidade:
  - Placas: Funciona em Arduinos com capacidade HID nativa, como Leonardo,
    Pro Micro e Due.
  - Bibliotecas: Requer as bibliotecas "Mouse.h" e "Keyboard.h".

  --------------------------------------------------------------------------------
  Hardware e Funções dos Pinos:
  --------------------------------------------------------------------------------
  BOTÕES DIRECIONAIS:
  * Pino 9 (Cima): Move o cursor para CIMA / Rola para CIMA (Modo Scroll) / Tecla SETA PARA CIMA (Modo Teclado).
  * Pino 8 (Baixo): Move o cursor para BAIXO / Rola para BAIXO (Modo Scroll) / Tecla SETA PARA BAIXO (Modo Teclado).
  * Pino 15 (Esquerda): Move o cursor para a ESQUERDA / Tecla SETA PARA A ESQUERDA (Modo Teclado).
  * Pino 10 (Direita): Move o cursor para a DIREITA / Tecla SETA PARA A DIREITA (Modo Teclado).

  BOTÕES DE AÇÃO (MOUSE):
  * Pino 7: Clique esquerdo do mouse.
  * Pino 3: Clique direito do mouse.
  * Pino 2: Clique duplo esquerdo.
  * Pino 4: Clique esquerdo longo (pressiona e trava; pressione novamente para soltar).

  BOTÕES DE MODO:
  * Pino 5: Ativa/Desativa o MODO SCROLL.
  * Pino 6: Ativa/Desativa o MODO TECLADO.

  --------------------------------------------------------------------------------
  Instruções e Funcionalidades:
  --------------------------------------------------------------------------------
  1. Modo Mouse (Padrão):
     - Controle o cursor com os botões direcionais.
     - Aceleração: Se um direcional for mantido pressionado por mais de 400ms,
       a velocidade do cursor aumenta progressivamente.
     - Use os botões de ação para os diferentes tipos de clique.

  2. Modo Scroll (Ativado pelo Pino 5):
     - Clique no botão do pino 5 para entrar/sair deste modo.
     - Enquanto estiver ativo, os botões Cima (Pino 9) e Baixo (Pino 8) controlam
       a roda de rolagem (scroll wheel) do mouse.
     - Pressionar qualquer outro botão de ação (cliques, modo teclado) desativa
       automaticamente o modo scroll.

  3. Modo Teclado (Ativado pelo Pino 6):
     - Clique no botão do pino 6 para entrar/sair deste modo.
     - Enquanto estiver ativo, os quatro botões direcionais se transformam nas
       setas do teclado, permitindo navegar em menus, textos, etc.
     - Pressionar qualquer outro botão de ação (cliques, modo scroll) desativa
       automaticamente o modo teclado.

  ================================================================================
*/

// --- Pinos dos botões ---
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
int d = 0; // Flag que indica se um direcional está pressionado (0 = não, 1 = sim)
unsigned long a = 0; // Armazena o tempo inicial do pressionamento (usar unsigned long para millis())
float t = 1.0; // Armazena a velocidade atual do cursor

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
    int scrollAmount = 0;
    if (upState) scrollAmount = 1;
    if (downState) scrollAmount = -1;
    
    if (scrollAmount != 0) {
      Mouse.move(0, 0, scrollAmount);
    }

  } else if (keyboardMode) {
    // Seta para Cima
    if (upState && !upArrowPressed) { Keyboard.press(KEY_UP_ARROW); upArrowPressed = true; }
    else if (!upState && upArrowPressed) { Keyboard.release(KEY_UP_ARROW); upArrowPressed = false; }
    // Seta para Baixo
    if (downState && !downArrowPressed) { Keyboard.press(KEY_DOWN_ARROW); downArrowPressed = true; }
    else if (!downState && downArrowPressed) { Keyboard.release(KEY_DOWN_ARROW); downArrowPressed = false; }
    // Seta para Esquerda
    if (leftState && !leftArrowPressed) { Keyboard.press(KEY_LEFT_ARROW); leftArrowPressed = true; }
    else if (!leftState && leftArrowPressed) { Keyboard.release(KEY_LEFT_ARROW); leftArrowPressed = false; }
    // Seta para Direita
    if (rightState && !rightArrowPressed) { Keyboard.press(KEY_RIGHT_ARROW); rightArrowPressed = true; }
    else if (!rightState && rightArrowPressed) { Keyboard.release(KEY_RIGHT_ARROW); rightArrowPressed = false; }
    
  } else {
    // --- MODO NORMAL (MOUSE) ---
    int xDistance = 0;
    int yDistance = 0;
    bool anyDirectionalPressed = upState || downState || rightState || leftState;

    // ***** LÓGICA DE ACELERAÇÃO REESTRUTURADA *****

    // 1. Se um direcional ACABOU de ser pressionado
    if (anyDirectionalPressed && d == 0) {
      d = 1;          // Ativa a flag de "pressionado"
      a = millis();   // Grava o tempo inicial
      t = range;      // Define a velocidade inicial
    }
    // 2. Se os direcionais ACABARAM de ser soltos
    else if (!anyDirectionalPressed && d == 1) {
      d = 0;          // Desativa a flag
      a = 0;          // Reseta o tempo
      t = range;      // Reseta a velocidade
    }

    // 3. Se um direcional ESTÁ sendo pressionado e o tempo de espera passou
    if (d == 1 && (millis() - a > TEMPO)) {
      t += MULTIPLI;  // Aumenta a velocidade (acelera)
    }

    // Só calcula o movimento se um botão estiver realmente pressionado
    if (d == 1) {
      xDistance = (rightState - leftState) * t;
      yDistance = (downState - upState) * t;
      
      if ((xDistance != 0) || (yDistance != 0)) {
        Mouse.move(xDistance, yDistance, 0);
      }
    }

    // --- Ações de clique ---
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
