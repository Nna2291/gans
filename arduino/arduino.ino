#include <ArduinoJson.h>

#include <SPI.h>
#include <UIPEthernet.h>
#include <microDS18B20.h>
// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C};
byte ip[] = {192, 168, 10, 3};

const uint8_t pin_Vm = A6;       // Вывод Arduino к которому подключён аналоговый выход модуля.
const float   Vcc    = 5.0f;                      // Напряжение питания Arduino.
const float   Vccm   = 3.3f;                      // Напряжение питания ОУ модуля (внутрисхемно используется 3,3В).
const float   Ka     = 1000.0f;                   // Множитель степенной функции (определяется калибровкой модуля). Можно получить функцией getKa().
const float   Kb     = -5.0f;                     // Степень   степенной функции (определяется калибровкой модуля). Можно получить функцией getKb().
const float   Kt     = 0.02f;                     // Температурный коэффициент (зависит от состава жидкости).
const float   Kp     = 0.5f;                      // Коэффициент пересчёта (зависит от состава жидкости).
const float   Kf     = 0.85f;                     // Коэффициент передачи ФВЧ+ФНЧ модуля (зависит от частоты переменного тока используемого для проведения измерений).
const float   T      = 25.0f;
// один датчик лучше читать без адресации, это сильно экономит память

MicroDS18B20<19> sensor;
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

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void m_on(int pi1, int pin2) {

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
  Ethernet.begin(mac, ip); // инициализация контроллера
  server.begin();          // включаем ожидание входящих соединений
  Serial.begin(9600);
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
    String method = response.substring(0, 4);
    Serial.println(method);
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
    else
    {
      sensor.requestTemp();
      float t   = 25.0f;                           // Указываем текущую температуру жидкости в °C.
      float Vm  = analogRead(pin_Vm) * Vcc / 1023; // Получаем напряжение на выходе модуля в Вольтах.
      float S   = Ka * pow((Vccm - Kf * Vm) / 2, Kb); // Получаем удельную электропроводность жидкости.
      float EC  = S / (1 + Kt * (sensor.getTemp() - T)); // Приводим удельную электропроводность жидкости к опорной температуре T.
      float TDS = EC * Kp;
      String aa = "{\"temp\":\"" + (String)sensor.getTemp() + "\", \"elek\":\"" + (String)S + "\", \"density\":\"" + (String)TDS + "\"}";
      client.println(F("HTTP/1.0 200 OK"));
      client.println(F("Content-Type: application/json"));
      client.println(F("Connection: close"));
      client.print(F("Content-Length: "));
      client.println("150 ");
      client.println();
      client.println(aa);
      client.stop();
    }
  }
}