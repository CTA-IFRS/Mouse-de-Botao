# LineButton

<img src="https://github.com/bruno-egami/Mouse-de-Botao/blob/LineButton/Fotos/IMG_20251007_174429.jpg?raw=true" height="250"> 

Este dispositivo destina-se a pessoas com limitações físico-motoras que possuem alguma dificuldade para utilizar o mouse convencional. 

Este mouse utiliza uma placa Arduino como controlador e a caixa pode ser confeccionada utilizando impressão 3D ou adquirindo uma caixa com dimensões necessárias para comportar todos os componentes.
A comunicação do mouse de botão com o computador é realizada por meio da porta USB, não sendo necessária a instalação de quaisquer softwares para sua utilização.

O dispositivo possui três modos de operação principais: Modo Mouse (padrão), Modo Scroll e Modo Teclado, permitindo uma ampla gama de interações com o computador.

  Compatibilidade:
  - Placas: Funciona em Arduinos com capacidade HID nativa, como Leonardo,
    Pro Micro e Due.
  - Bibliotecas: Requer as bibliotecas padrão "Mouse.h" e "Keyboard.h".

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


**Teclas de função:**

- Ao acionar a função scroll (tecla preta com setas verticais) o mouse entra em modo de rolagem, permitindo utilizar as teclas direcionais cima/baixo em botões de rolagem de página (similar ao rolarmos o botão central de um mouse tradicinal);
- Ao acionar a função “teclado” (tecla preta com setas nas 4 direções) o mouse entra em modo “teclado” (preciso pensar em um nome melhor para esta função), permitindo utilizar as teclas direcionais para movimentação do cursor quando em modo de edição de texto (avançar, retroceder, subir ou descer o cursor de seleção) ou movimentação da página da mesma forma que utilizamos as teclas direcionais em um teclado convencional.

Em ambos os casos, para retornar a função “normal” do mouse, basta acionar qualquer tecla de ação (qualquer botão colorido, exceto os botões brancos).

Para maiores informações e instruções de confecção e uso:
[Livro – Conexões Assistivas: Tecnologia Assistiva e Materiais Didáticos Acessíveis](https://drive.google.com/file/d/1_BM6zQywOF1XtAiU45MmOcAh9_2PgRoI/view) (página 38)

# Atualização do mouse linha com:

- colmeia para evitar acionamento acidental das teclas;
- melhoria no sistema de fixação dos switches (todo o suporte é cortado na laser, sem necessidade de peças impressas);
- melhoria no código (principal mudança foi a substituição da função stickbutton e keyboardmode para as teclas direcionais).
- código revisado e atualizado.

# Incluídas imagens do processo de montagem:

1. Corte de todas as peças em MDF 3mm;
2. Colagem das peças em MDF (exceto colméia superior). A colagem pode ser realizada com cola instantânea, cola branca ou cola quente.;
3. Montagem dos switches (modelo KW11-7-1 2T ou 3T, utilizar terminais NO);
4. Montagem dos circuitos (arduino>switches);
5. Corte e gravação das teclas (acrílico 3mm de diversas cores), atentar para as layers/cores do arquivo DXF (branco>corte, azul> corte com velocidade alta e baixa potência (apenas para gerar as ranhuras e vermelho para gravação);
6. Pintura das teclas (marcador permanete para as teclas em cores claras e tinta acrílica/PVA para as cores escuras);
7. Montagem da colméia e posicionamento das teclas).

Observações: Atentar para as layers/cores do arquivo DXF das teclas.





# Outras variações deste recurso estão disponíveis nos seguintes links:

[**Mouse de botão**](https://github.com/CTA-IFRS/Mouse-de-Botao/tree/main)

<img src="https://cta.ifrs.edu.br/wp-content/uploads/sites/3/2021/05/Captura-de-Tela-2021-05-05-a%CC%80s-11.13.56-e1620267197687.png" height="250"> 

[**Joystick**](https://github.com/CTA-IFRS/Mouse-de-Botao/tree/JoystickD)

<img src="https://github.com/CTA-IFRS/Mouse-de-Botao/blob/JoystickD/Mouse-Joystick.jpeg?raw=true" height="250">

[**Joystick Analógico**](https://github.com/CTA-IFRS/Mouse-de-Botao/tree/JoystickA) // trocar imagem e link

<img src="https://github.com/CTA-IFRS/Mouse-de-Botao/blob/JoystickD/Mouse-Joystick.jpeg?raw=true" height="250">

[**Mouse de Rolos**](https://github.com/CTA-IFRS/Mouse-de-rolos)

<img src="https://github.com/CTA-IFRS/Mouse-de-rolos/blob/main/Mouse-Rolos.jpeg?raw=true" height="250">
