# EmbarcaTech   
### TAREFA 2 - U4C2O1234A - V1, Unidade 4 - Capítulo 1
#### Grupo 4 - Subgrupo 7
#### Integrantes:
* Marcel Mascarenhas Andrade
* Davi Nascimento Leao
* Hilquias Rodrigues de Oliveira
* Roberto Vítor Lima Gomes Rodrigues
* Kaique Rangel Da Silva

#### Vídeo de funcionamento
https://drive.google.com/drive/u/2/folders/12cpkTtdwp6IipmoCbu_QZU_cP92SQ7P2

#### Instruções de compilação
Certifique-se de que você tem o ambiente configurado conforme abaixo:
* Pico SDK instalado e configurado.
* VSCode com todas as extensões configuradas, CMake e Make instalados.
* Clone o repositório e abra a pasta do projeto, a extensão Pi Pico criará a pasta build
* Clique em Compile na barra inferior, do lado direito (ao lado esquerdo de RUN | PICO SDK)
* Localize o arquivo gpio_control.uf2
* Conecte a BitDogLab ao computador via USB enquanto pressiona o botão BOOTSEL.
* Observe que o microcontrolador aparece como uma unidade de disco no computador.
* Arraste e solte o arquivo .uf2 gerado para a unidade que apareceu.
* Após o upload, o microcontrolador reiniciará automaticamente e estará pronto para receber comandos via UART.
* Abra o PuTTY, escolha o tipo de conexão Serial e configure a porta COM em que seu dispositivo está, com a velocidade 115200:
    * Na aba Terminal, selecione os checkboxes Force On nas duas linhas de Line Disciple Options
    * Na aba Connections, clique em Serial, e selecione o item do dropdown de flow control para None
    * Na aba Session, clique em Open
    * Digite VERDE, VERMELHO, AZUL e SOM para ativar os leds Verde, Vermelho, Azul e o Buzzer, respectivamente, e digite qualquer outra coisa para desligá-los.

