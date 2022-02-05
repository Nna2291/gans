#include <Arduino.h>
#include <SPI.h>
#include <UIPEthernet.h>
#define DV11 4
#define DV12 5

#define DV21 6
#define DV22 7

#define DV31 8
#define DV32 9

#define DV41 2
#define DV42 12

#define INA 15 // выходы arduino
#define INB 16
#define EN 14
#define PWM A3

String deletee = ",";
int dviga[] = {DV11, DV12, DV21, DV22, DV31, DV32, DV41, DV42};
int motorSpeed;
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C}; // MAC-адрес
byte ip[] = {192, 168, 10, 3};                     // IP-адрес
byte myDns[] = {192, 168, 10, 1};                  // адрес DNS-сервера
byte gateway[] = {192, 168, 10, 1};                // адрес сетевого шлюза
byte subnet[] = {255, 255, 255, 0};                // маска подсети

EthernetServer server(2000);            // создаем сервер, порт 2000
EthernetClient client;                  // объект клиент
boolean clientAlreadyConnected = false; // признак клиент уже подключен
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void setup()
{
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(PWM, OUTPUT);
  digitalWrite(EN, HIGH);
  for (auto number : dviga)
  {
    pinMode(number, OUTPUT);
  }
  Ethernet.begin(mac, ip, myDns, gateway, subnet); // инициализация контроллера
  server.begin();                                  // включаем ожидание входящих соединений
  Serial.begin(9600);                              // выводим IP-адрес контроллера
}
void on_head(int speeed)
{
  digitalWrite(INA, LOW); // крутим мотор в одну сторону
  digitalWrite(INB, HIGH);
  analogWrite(PWM, motorSpeed);
}

void on_r_head(int speeed)
{
  digitalWrite(INA, HIGH); // крутим мотор в противоположную сторону
  digitalWrite(INB, LOW);
  analogWrite(PWM, motorSpeed);
}

void off_head()
{
  digitalWrite(INA, LOW); // крутим мотор в противоположную сторону
  digitalWrite(INB, LOW);
}

void on(int D1, int D2)
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
}

void off(int D1, int D2)
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
}

void on_r(int D1, int D2)
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
}

void loop()
{
  String message;
  String task;
  int value;
  client = server.available(); // ожидаем объект клиент
  if (client)
  {
    // есть данные от клиента
    if (clientAlreadyConnected == false)
    {
      clientAlreadyConnected = true;
    }

    while (client.available() > 0)
    {
      char chr = client.read(); // чтение символа
      server.write(chr);
      message += String(chr);
    }
    Serial.println(message);
    switch (message[0])
    {

    case 'd':
      task = message.substring(1);
      on(getValue(task, ',', 0).toInt(), getValue(task, ',', 1).toInt());
      break;
    case 's':
      task = message.substring(1);
      off(getValue(task, ',', 0).toInt(), getValue(task, ',', 1).toInt());
      break;
    case 'm':
      value = message.substring(1).toInt();
      on_head(value);
      break;
    case 'r':
      value = message.substring(1).toInt();
      on_r_head(value);
      break;
    case 'o':
      off_head();
      break;
    }
  }
}
