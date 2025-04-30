# Medidor de Energia

**Descrição:**  
Aplicação de Cloud, IoT e Indústria 4.0 desenvolvida em Python, com componentes adicionais em C++ e HTML.

---

## 📂 Estrutura do Repositório

O repositório é organizado em diferentes diretórios, cada um com arquivos específicos para a funcionalidade do projeto:

### Diretórios Principais:
- **`Projeto/Medidorde energia em tempo real/Biblioteca SD.h/SD`**  
  Contém bibliotecas e exemplos para o uso de cartões SD, incluindo o código fonte para testar e ler informações de um cartão SD.

- **`Projeto/Medidorde energia em tempo real/Arquivos da WebPage para colocar no cartãoSD/Arquivos SD`**  
  Inclui arquivos da interface web para serem armazenados no cartão SD. Exemplo de arquivos neste diretório:
  - `index.htm`: Página HTML com interface para monitoramento de consumo de energia em tempo real.
  - `gauge_license.txt`: Detalhes da licença para o uso de componentes gauge.
  - Arquivos compactados para facilitar o uso em diferentes sistemas.

- **`Programade instalação`**  
  Scripts e instaladores necessários para configuração, como o driver `CH34x_Install_Windows_v3_4.zip`.

---

## 🛠️ Tecnologias Utilizadas

O projeto utiliza as seguintes linguagens e tecnologias:

- **C++** (82.7%)  
  Principalmente usado para o desenvolvimento do firmware que opera o medidor de energia em tempo real e a interação com o cartão SD.

- **C** (13.8%)  
  Usado em bibliotecas auxiliares e funções de baixo nível.

- **HTML** (3.5%)  
  Utilizado para a interface web responsiva que exibe os dados da aplicação IoT.

---

## 📋 Licenças

O projeto utiliza diferentes licenças para seus componentes:

- **Gauge Component**  
  Licenciado sob a MIT License, conforme detalhado no arquivo `gauge_license.txt`. Mais informações disponíveis em [canv-gauge](https://github.com/Mikhus/canv-gauge).

- **SD Library**  
  A biblioteca SD é licenciada sob a GNU General Public License (GPL) versão 3 ou superior. Detalhes no arquivo `README.adoc` no diretório `Biblioteca SD.h`.

---

## 🔧 Como Configurar

1. **Dependências de Hardware**:  
   - Um cartão SD configurado adequadamente.
   - Shield ou módulo SD compatível com Arduino.
   - Conexões SPI para o cartão SD:
     - MOSI: Pino 11 (Arduino Uno)
     - MISO: Pino 12 (Arduino Uno)
     - CLK: Pino 13 (Arduino Uno)
     - CS: Pino 4 (ou conforme o shield utilizado).

2. **Configuração de Software**:
   - Inclua a biblioteca `SD.h` no ambiente de desenvolvimento do Arduino.
   - Carregue o sketch `CardInfo.ino` (localizado no diretório `Biblioteca SD.h/SD/SD/examples/CardInfo`) no Arduino IDE para testar a leitura do cartão SD.

3. **Interface Web**:  
   - Copie os arquivos do diretório `Arquivos da WebPage para colocar no cartãoSD/Arquivos SD` para o cartão SD.
   - Insira o cartão SD no sistema e acesse a interface via navegador para visualizar o consumo de energia.

4. **Driver de Instalação**:  
   - Execute o instalador `CH34x_Install_Windows_v3_4.zip` para configurar os drivers necessários no Windows.

---

## 🚀 Funcionalidades

- **Monitoramento em Tempo Real**  
  A interface exibe:
  - **Potência (W)**.
  - **Corrente (A)**.
  - **Consumo (R$)**.

- **Compatibilidade com SD**  
  Teste e leitura de cartões SD com suporte aos formatos FAT16 e FAT32.

- **Visualização Gráfica**  
  Utilização de gauges para representar dados em tempo real.

---

## 📝 Documentação Adicional

- **Referência da Biblioteca SD**:  
  Mais informações sobre a biblioteca SD podem ser encontradas em [Arduino SD Reference](http://www.arduino.cc/en/Reference/SD).

---

## 📂 Estrutura de Arquivos

### Exemplos de Arquivos Importantes:

- **`index.htm`**  
  Interface web para o monitoramento de consumo de energia em tempo real.

- **`CardInfo.ino`**  
  Código de exemplo para testar a funcionalidade do cartão SD.

- **`README.adoc`**  
  Detalhes e licença da biblioteca SD.

- **`CH34x_Install_Windows_v3_4.zip`**  
  Driver para configurar a comunicação com o dispositivo.

---

## 🖊️ Autor

- **zaleoz1**  
  Criador e mantenedor do projeto.
