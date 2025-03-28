
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#define pino2 2

const char* ssid = "Isalan Guimarães";
const char* password = "isalan7447";

Espalexa espAlexa;

void Funcion_pino2(uint8_t brightness);



void setup() {
  Serial.begin(115200);
  pinMode(pino2, OUTPUT);
  digitalWrite(pino2, HIGH);
  ConexaoWifi();
  espAlexa.addDevice("luz", Funcion_pino2);
  espAlexa.begin();
}

void loop() {
  ConexaoWifi();
  espAlexa.loop();
  delay(1);
}

// Função para conectar com WIFI
void ConexaoWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("Conectado para ");
    Serial.println(ssid);
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
    //IP fixo. Você pode alterar conforme a sua rede
  IPAddress ip(192, 168, 10, 11);
  IPAddress gateway(192, 168, 10, 1);
  IPAddress subnet(255, 255, 255, 0);
  Serial.print("Configurando IP fixo para : ");
  Serial.println(ip);

  //Envia a configuração
  WiFi.config(ip, gateway, subnet);
  Serial.print("Server em: ");
  Serial.println(WiFi.localIP());

  }
}

// Função para o  pino2
void Funcion_pino2(uint8_t brightness) {
  if (brightness) {
    digitalWrite(pino2, HIGH);
  }
  else {
    digitalWrite(pino2, LOW);
  }
}
