# Space Invaders - Roguelike Edition

## Descrição

Este é um clássico **Space Invaders** desenvolvido por nossa equipe usando a biblioteca **raylib** (v1.3). O jogo é uma recriação moderna do clássico, com a adição de funcionalidades como waves progressivas de inimigos e disparos automáticos. O jogador controla uma nave espacial e deve derrotar os inimigos que aparecem em ondas, enquanto tenta evitar colisões.

Os inimigos são gerados em **waves** (ondas), com cada wave aumentando a dificuldade.

## Objetivo

- **Sobreviver às ondas de inimigos**: Derrote todas as ondas sem deixar que os inimigos colidam com sua nave.
- **Acumular pontos**: Ganhe pontos ao eliminar inimigos e sobreviver ao maior número de waves possível.

## Controles

- **Setas direcionais**: Movimentam a nave do jogador (direita, esquerda, cima, baixo).
- **[P]**: Pausar ou despausar o jogo.
- **[Enter]**: Reinicia o jogo após a derrota.

### Jogabilidade

- O jogo começa com o jogador controlando uma nave posicionada no centro da parte inferior da tela.
- Inimigos são gerados no topo e descem pela tela em um movimento contínuo.
- O jogador dispara automaticamente, e o objetivo é acertar os inimigos antes que colidam com a nave.
- O jogo possui **3 waves**:
  - **Wave 1**: 10 inimigos.
  - **Wave 2**: 20 inimigos.
  - **Wave 3**: 50 inimigos.
- O jogo termina se todos os inimigos forem derrotados ou se um inimigo colidir com o jogador.
