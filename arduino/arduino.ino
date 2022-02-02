#include <SPI.h>
#include <UIPEthernet.h>
#define DV1 6
#define DV2 7
// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C}; // MAC-адрес
byte ip[] = {192, 168, 10, 3}; // IP-адрес
byte myDns[] = {192, 168, 10, 1}; // адрес DNS-сервера
byte gateway[] = {192, 168, 10, 1}; // адрес сетевого шлюза
byte subnet[] = {255, 255, 255, 0}; // маска подсети
bool trys_bool = false;
int trys_int = 0;
bool tryso_bool = false;

EthernetServer server(2000); // создаем сервер, порт 2000
EthernetClient client; // объект клиент
boolean clientAlreadyConnected = false; // признак клиент уже подключен

void setup() {
  pinMode(7, OUTPUT);
  pinMode(DV2, OUTPUT);
  pinMode(DV1, OUTPUT);
  digitalWrite(DV2, LOW);
  digitalWrite(DV1, LOW);
  Ethernet.begin(mac, ip, myDns, gateway, subnet); // инициализация контроллера
  server.begin(); // включаем ожидание входящих соединений
  Serial.begin(9600); // выводим IP-адрес контроллера
}
void trys(int i) {
  digitalWrite(7, HIGH);
  delay(i);
  digitalWrite(7, LOW);
  delay(i);
}
void tryso() {
  digitalWrite(7, LOW);
}
void on() {
  digitalWrite(DV1, HIGH);
  digitalWrite(DV2, LOW);
}
void off() {
  digitalWrite(DV1, LOW);
  digitalWrite(DV2, LOW);

}




void loop() {
  String message;
  client = server.available(); // ожидаем объект клиент
  if (client) {
    // есть данные от клиента
    if (clientAlreadyConnected == false) {
      clientAlreadyConnected = true;
    }

    while (client.available() > 0) {
      char chr = client.read(); // чтение символа
      server.write(chr);
      message += String(chr);
    }
    Serial.println(message);
    switch (message[0])
    {
      case 'd':
        trys_int = message.substring(1).toInt();
        trys_bool = true;
        break;
      case 's':
        trys_bool = false;
        digitalWrite(7, LOW);
        break;
    }
  }
  if (trys_bool == true) {
    trys(trys_int);
  }
}