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
bool work = false;
bool df = false;

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
void trys() {
  digitalWrite(7, HIGH);
  delay(200);
  digitalWrite(7, LOW);
  delay(200);
}
void tryso() {

  digitalWrite(7, HIGH);
  delay(50);
  digitalWrite(7, LOW);
  delay(50);
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
  if (work == true) {
    trys();
  }
  if (df == true){
    tryso();
    }
  client = server.available(); // ожидаем объект клиент
  if (client) {
    // есть данные от клиента
    if (clientAlreadyConnected == false) {
      // сообщение о подключении
      Serial.println("Client connected");
      client.println("Server ready"); // ответ клиенту
      clientAlreadyConnected = true;
    }

    while (client.available() > 0) {
      char chr = client.read(); // чтение символа
      server.write(chr); // передача клиенту
      Serial.write(chr);
      switch (chr)
      {
        case 'd':
          work = true;
          break;
        case 's':
          work = false;
          break;
        case 'k':
          df = true;
          break;
        case 'p':
          df = false;
          break;
        default:
          digitalWrite(7, HIGH);
          break;
      }
    }
  }
}