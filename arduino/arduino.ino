#include <ArduinoJson.h>

#include <SPI.h>
#include <UIPEthernet.h>
// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C};
byte ip[] = {192, 168, 10, 3};

StaticJsonDocument<30> doc;
StaticJsonDocument<30> task;
EthernetServer server(80);              // создаем сервер, порт 80
EthernetClient client;                  // объект клиент
boolean clientAlreadyConnected = false; // признак клиент уже подключен
int pin;
boolean work_led = false;
int led_speed;

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
  pinMode(7, OUTPUT);
  Ethernet.begin(mac, ip); // инициализация контроллера
  server.begin();          // включаем ожидание входящих соединений
  Serial.begin(9600);
}

void loop()
{
  String response;
  client = server.available(); // ожидаем объект клиент
  if (work_led == true)
  {
    digitalWrite(pin, HIGH);
    delay(led_speed);
    digitalWrite(pin, LOW);
    delay(led_speed);
  }
  else
  {
    digitalWrite(pin, LOW);
  }
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
    String method = response.substring(0, 4);
    if (method == "POST")
    {
      String json = response.substring(response.indexOf("Content-Type: application/json") + 34);
      deserializeJson(task, json);
      char *task_s = task["task"];
      String task_string = String(task_s);
      Serial.println(task_string);
      if (getValue(task_string, ',', 0) == "ON")
      {
        pin = getValue(task_string, ',', 1).toInt();
        led_speed = getValue(task_string, ',', 2).toInt();
        work_led = true;
      }
      else if (getValue(task_string, ',', 0) == "OF")
      {
        pin = getValue(task_string, ',', 1).toInt();
        digitalWrite(pin, LOW);
        work_led = false;
      }
      client.println(F("HTTP/1.0 200 OK"));
      client.println(F("Connection: close"));
      client.stop();
    }
    else if (method == "GET ")
    {
      doc["value"] = analogRead(A2);
      // Write response headers
      client.println(F("HTTP/1.0 200 OK"));
      client.println(F("Content-Type: application/json"));
      client.println(F("Connection: close"));
      client.print(F("Content-Length: "));
      client.println(measureJsonPretty(doc));
      client.println();
      serializeJsonPretty(doc, client);
      client.stop();
    }
  }
}