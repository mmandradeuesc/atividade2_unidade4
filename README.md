# EmbarcaTech   
### TAREFA 2 - U4C2O1234A - V1, Unidade 4 - Capítulo 1
#### Grupo 4 - Subgrupo 7
#### Integrantes:
* Marcel Mascarenhas Andrade
* Davi Nascimento Leao
* Hilquias Rodrigues de Oliveira
* Kaique Rangel Da Silva



#### Instruções de compilação
Certifique-se de que você tem o ambiente configurado conforme abaixo:
Pico SDK instalado e configurado.
CMake e Make instalados.
Editor de código, como VS Code.
Ferramenta de simulação, como Wokwi, configurada no VS Code.
Etapas de Compilação

Clone este repositório:
bash
Copiar
Editar
git clone <https://github.com/mmandradeuesc/atividade2_unidade4>
cd <atividade2_unidade4>

Crie uma pasta build para organizar os arquivos de compilação:
bash
Copiar
Editar
mkdir build
cd build

Configure o projeto utilizando o CMake:
bash
Copiar
Editar
cmake ..

Compile o código:
bash
Copiar
Editar
make

Localize o arquivo .uf2 gerado na pasta build. Este é o binário que deve ser carregado no microcontrolador.

* ##### Alternativamente

Executando no Microcontrolador
Conecte o RP2040 ao computador via USB enquanto pressiona o botão BOOTSEL.
Monte o microcontrolador como uma unidade de disco no computador.
Arraste e solte o arquivo .uf2 gerado para a unidade montada.
Após o upload, o microcontrolador reiniciará automaticamente e estará pronto para receber comandos via UART.

Caso prefira testar a funcionalidade no simulador Wokwi sem usar o hardware real:
Abra o projeto no VS Code.
Certifique-se de que a extensão Wokwi está instalada.
Execute o projeto no simulador Wokwi:
No menu do VS Code, clique em Run > Start Debugging (ou pressione F5).
O simulador Wokwi será iniciado, permitindo testes sem o hardware.
