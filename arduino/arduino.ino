#include <ArduinoJson.h>

#include <SPI.h>
#include <UIPEthernet.h>
// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C};
byte ip[] = {192, 168, 10, 3};


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
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void m_on(int pi1, int pin2){

}

void dv_on(int pin1, int pin2) {
  Serial.println("*************");
  Serial.println("ON");
  Serial.println(pin1);
  Serial.println(pin2);
  Serial.println("*************");
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void dv_off(int pin1, int pin2) {
  Serial.println("*************");
  Serial.println("OFF");
    Serial.println(pin1);
  Serial.println(pin2);
  Serial.println("*************");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

void dv_r(int pin1, int pin2) {
  Serial.println("*************");
  Serial.println("R");
    Serial.println(pin1);
  Serial.println(pin2);
  Serial.println("*************");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  digitalWrite(17, HIGH);
  digitalWrite(16, HIGH);
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
      String json = response.substring(response.indexOf("{"));
      deserializeJson(task, json);
      char *task_s = task["task"];
      String task_string = String(task_s);
      Serial.println(task_string);
      if (task_string.substring(0, 2) == "DO")
      {
        String p1 = getValue(task_string, ';', 1);
        String p2 = getValue(task_string, ';', 2);
        dv_on((p1).toInt(), (p2).toInt());
      }
      else if (task_string.substring(0, 2) == "DR")
      {
        String p1 = getValue(task_string, ';', 1);
        String p2 = getValue(task_string, ';', 2);
        dv_r((p1).toInt(), (p2).toInt());
      }
      else if (task_string.substring(0, 2) == "DV")
      {
        String p1 = getValue(task_string, ';', 1);
        String p2 = getValue(task_string, ';', 2);
        dv_off((p1).toInt(), (p2).toInt());
      }
      client.println(F("HTTP/1.0 200 OK"));
      client.println(F("Connection: close"));
      client.stop();
    }

  }
}