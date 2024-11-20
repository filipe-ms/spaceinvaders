# Space Invaders - Roguelike Edition



Este é um clássico desenvolvido por nossa equipe usando a biblioteca **raylib** (v1.3). O jogo é uma recriação moderna do clássico, com a adição de funcionalidades como waves progressivas de inimigos e disparos automáticos. O jogador controla uma nave espacial e deve derrotar os inimigos que aparecem em ondas, enquanto tenta evitar colisões.
# Instruções para Configuração do Jogo

Para executar este jogo em uma distribuição Linux, siga os passos abaixo para instalar as dependências necessárias:

### Pré-requisitos
Certifique-se de que você tenha acesso root (sudo) e uma conexão com a internet.

### Passos
1. Clonar nosso repositório numa pasta chamada "Space" (case sensitive)

Segue o diagrama de pastas:

\Space
├── .vscode/
├── bin/
├── build/
├── include/
├── resources/
├── src/
├── .gitignore
├── build-MinGW-W64.bat
├── build-VisualStudio2022.bat
├── linux.sh
├── Makefile
├── New Text Document.txt
├── README.md
└── Space.sln

2. **Atualize os pacotes do sistema**  
   Execute os seguintes comandos para garantir que seu sistema esteja atualizado:
   ```bash
   sudo apt-get upgrade && sudo apt-get update
   ```

3. **Instale o `make`**  
   O `make` é necessário para compilar o jogo. Instale-o com o comando:
   ```bash
   sudo apt-get install make
   ```

4. **Instale o `cmake` e outras ferramentas de build**  
   O `cmake` e o `build-essential` são usados para compilar o código do jogo. Instale-os com:
   ```bash
   sudo apt-get update && sudo apt-get install cmake build-essential
   ```

5. **Instale as dependências gráficas**  
   Certifique-se de que as bibliotecas necessárias para gráficos estejam instaladas:
   ```bash
   sudo apt-get install libx11-dev xserver-xorg-dev xorg-dev
   ```

6. **Execute o arquivo .sh**


Para facilitar a instalação e execução do jogo, você pode usar o script `linux.sh` disponível no diretório raiz do projeto.

1. **Torne o script executável (apenas uma vez):**  
   Execute o seguinte comando no terminal enquanto estiver no diretório raiz do projeto:
   ```bash
   chmod +x linux.sh
   ```

2. **Execute o script:**  
   Após tornar o script executável, rode:
   ```bash
   ./linux.sh
   ```

3. **Caso prefira não usar o `chmod`:**  
   Você pode executar o script diretamente com o comando:
   ```bash
   sh linux.sh
   ```

### Observações
- Se você enfrentar algum problema, verifique se todas as dependências foram instaladas corretamente.
- Certifique-se de ter permissões adequadas no diretório onde o jogo será executado.
