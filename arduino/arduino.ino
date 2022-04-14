#include <SPI.h>
#include <UIPEthernet.h>
#include <microDS18B20.h>
#include "MPU6050.h"
MPU6050 mpu;
// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C};
byte ip[] = {192, 168, 1, 3};

MicroDS18B20<14> sensor;
EthernetServer server(80);              // создаем сервер, порт 80
EthernetClient client;                  // объект клиент
boolean clientAlreadyConnected = false;

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  Ethernet.begin(mac, ip); // инициализация контроллера
  server.begin();
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();
  Serial.println("ok");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  String response;
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
      response += chr;
    }
    if (response.substring(0, 4) == "POST")
    {
      String task_string = response.substring(response.indexOf("!") + 1);
      if (task_string.substring(0, 2) == "DO")
      {
        digitalWrite(getValue(task_string, ';', 1).toInt(), HIGH);
        digitalWrite(getValue(task_string, ';', 2).toInt(), LOW);
      }
      else if (task_string.substring(0, 2) == "DR")
      {
        digitalWrite(getValue(task_string, ';', 1).toInt(), LOW);
        digitalWrite(getValue(task_string, ';', 2).toInt(), HIGH);
      }
      else if (task_string.substring(0, 2) == "DV")
      {
        digitalWrite(getValue(task_string, ';', 1).toInt(), LOW);
        digitalWrite(getValue(task_string, ';', 2).toInt(), LOW);
      }
      client.println(F("HTTP/1.0 200 OK"));
      client.println(F("Connection: close"));
      client.stop();
    }
    else
    {
      sensor.requestTemp();
      int16_t ax = mpu.getAccelerationZ();  // ускорение по оси Х
      // стандартный диапазон: +-2g
      ax = constrain(ax, -16384, 16384);
      String aa = (String)sensor.getTemp() + ";" + analogRead(A6) + ";" + (String)ax;
      client.println(F("HTTP/1.0 200 OK"));
      client.println(F("Content-Type: application/json"));
      client.println(F("Connection: close"));
      client.print(F("Content-Length: "));
      client.println(F("150"));
      client.println();
      client.println(aa);
      client.stop();
    }
  }
}