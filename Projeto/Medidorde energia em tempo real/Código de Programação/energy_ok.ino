
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "EmonLib.h"


EnergyMonitor SCT013; //Objeto criado para o sensor SCT-013
 
int pinSCT = A1;   //Pino analógico conectado ao SCT-013
 
//Váriáveis globais
int tensao = 110;
float Valor=0.000135;
float KWH=0;
float potencia=0;
float y=0;
float x=0;

//tamanho do buffer usado para capturar solicitações HTTP
#define REQ_BUF_SZ   50

//Endereço MAC do Shield Ethernet Onboard
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 20); // endereço IP, pode ser necessário alterar dependendo da sua rede
EthernetServer server(80);  // cria um servidor na porta 80
File webFile;             // o arquivo da página da web no cartão SD
char HTTP_req[REQ_BUF_SZ] = {0}; // solicitação HTTP em buffer armazenada como sequência terminada nula
char req_index = 0;              // indexa no buffer HTTP_req

void setup()
{
    // desabilita Ethernet Shield
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    Serial.begin(9600);       // para depuração
    
  // inicializa o SD card
   Serial.println("Inicializando o SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERRO - inicialização do SD card falhou!");
        return;    
    }
    Serial.println("SUCCESSO - SD card inicializado");
    // checa o arquivo index.htm 
    if (!SD.exists("index.htm")) {
        Serial.println("ERRO - Arquivo index.htm não encontrado!");
        return;  // se não encontrar o arquivo index.html
    }
    Serial.println("SUCCESSO - Arquivo index.htm encontrado.");
   
    Ethernet.begin(mac, ip);  // Inicializando o Shield Ethernet 
    server.begin();  // Inicia e aguarda conexão de cliente
    SCT013.current(pinSCT, 6.0607);//inicializa o sensor, calibrado com resistor de 330 Ohms
}

void loop()
{
  
  
  
  EthernetClient client = server.available();  // try to get client

  if (client) {  // se obteve cliente,
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // dados do cliente disponíveis para leitura
                char c = client.read(); // lê 1 byte (caractere) do cliente
                 // buffer primeira parte da solicitação HTTP na matriz HTTP_req (string)
              // deixa o último elemento na matriz como 0 para a sequência de terminação nula (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;        // salva o caractere de solicitação HTTP
                    req_index++;
                           }
              // a última linha da solicitação do cliente está em branco e termina com \ n
                // responde ao cliente somente após a última linha recebida
                if (c == '\n' && currentLineIsBlank) {
                  // envia um cabeçalho de resposta http padrão
                    client.println("HTTP/1.1 200 OK");
                    // o restante do cabeçalho segue abaixo, dependendo se
                    // página da web ou página XML é solicitada
                    // Solicitação Ajax - envia arquivo XML
                    if (StrContains(HTTP_req, "ajax_inputs")) {
                    // envia o restante do cabeçalho HTTP
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();
                      // envia arquivo XML contendo estados de entrada
                        XML_response(client);
                    }
                    else { // se houver a solicitação de página da web
                        // envia o restante do cabeçalho HTTP
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // envia a página da web
                        webFile = SD.open("index.htm");       //abre o arquivo index.html do SD card
                        if (webFile) {
                            while(webFile.available()) {
                                client.write(webFile.read()); // envia a web page para o cliente
                            }
                            webFile.close();
                        }
                    }
                   // exibe a solicitação HTTP recebida na porta serial
                    Serial.print(HTTP_req);
                 // redefine o índice do buffer e todos os elementos do buffer para 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
             // toda linha de texto recebida do cliente termina com \ r \ n
                if (c == '\n') {
                    // último caractere na linha do texto recebido
                    // iniciando nova linha com o próximo caractere lido
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
               // um caractere de texto foi recebido do cliente
                    currentLineIsBlank = false;
                }
            } 
        } 
        delay(1);      // dá tempo ao navegador da Web para receber os dados
        client.stop(); // encerra a conexão
    } 
       
     double Irms = SCT013.calcIrms(1480);   // Calcula o valor da Corrente, usando 1480 amostras
     if(Irms<0.02){Irms=0; potencia=0;} 
     potencia = Irms * tensao;
   
     KWH = potencia/1000;
     delay(1000); //Espera 1 segundo
     x=(((potencia)/1000)*Valor); //calcula e guarda em x o valor do consumo em reais
     y=y+x; //após 1 segundo, soma e guarda em y o valor de x
    
  
}

// envia o arquivo XML contendo os valores das variáveis para a web page
void XML_response(EthernetClient cl)
{
    float analog_val;
    float analog_val2;
    float analog_val3;
    
    
    cl.print("<?xml version = \"1.0\" ?>");
    cl.print("<inputs>");
   // Lê o valor da corrente
    double Irms = SCT013.calcIrms(1480);   // Calcula o valor da Corrente
   
    if(Irms<0.02){Irms=0; potencia=0;} 
    analog_val = potencia;
    cl.print("<analog>");
    cl.print(analog_val);  
    cl.print("</analog>");
    
    analog_val2 = Irms;
    cl.print("<analog>");
    cl.print(analog_val2);
    cl.print("</analog>");


     analog_val3 = y;
    cl.print("<analog>");
    cl.print(analog_val3,8);
    cl.print("</analog>");
    cl.print("</inputs>");
    
     
}

//
// define cada elemento da string str como 0 (limpa a matriz)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// procura a string sfind na string str
// retorna 1 se a sequência for encontrada
// retorna 0 se a sequência não for encontrada
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }
    return 0;
}
