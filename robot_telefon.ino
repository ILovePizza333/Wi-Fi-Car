#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Sanj";// имя  точки доступа которую создаст машина (англ. буквы и можно несколько цифр) не менее 3
const char* password = "12345678";// пароль точки доступа(англ. буквы или цифры) не менее 8 символов
int forw_left_velocity = 1023; // скорость левого двигателя вперед(0-1023)
int forw_right_velocity = 970;// скорость правого двигателя вперед(0-1023)
int back_left_velocity = 1023; // скорость левого двигателя назад(0-1023)
int back_right_velocity = 970;// скорость правого двигателя назад(0-1023)
int val = 0;
int sk = 2;
int pv = 0;
#define LED D13
#define dv_left_forw D3 //пин левый вперед
#define dv_left_back D11 //пин левый назад
#define dv_right_forw D10 //пин правый вперед
#define dv_right_back D4 //пин правый назад
ESP8266WebServer server(80);

void forw_handler() {
  Serial.println("forw");
  analogWrite (dv_left_forw, forw_left_velocity / sk);
  analogWrite (dv_right_forw, forw_right_velocity / sk);

  digitalWrite(dv_right_back, LOW);
  digitalWrite(dv_left_back, LOW);

  server.send(200, "text/plain", "OK");
}
void stop_handler() {
  Serial.println("stop");
  digitalWrite (dv_right_forw, LOW);
  digitalWrite(dv_right_back, LOW);
  digitalWrite(dv_left_back, LOW);
  digitalWrite (dv_left_forw, LOW);
  server.send(200, "text/plain", "OK");
}
void back_handler() {
  Serial.println("back");
  analogWrite (dv_left_back, back_left_velocity / sk);
  analogWrite (dv_right_back, back_right_velocity / sk);
  digitalWrite (dv_right_forw, LOW);
  digitalWrite (dv_left_forw, LOW);
  server.send(200, "text/plain", "OK");
}
void left_handler() {
  Serial.println("left");
  if (pv == 1) {
    analogWrite (dv_left_back, back_left_velocity / sk);
    analogWrite (dv_right_forw, forw_right_velocity / sk);
    digitalWrite(dv_right_back, LOW);
    digitalWrite (dv_left_forw, LOW);

  } else {
    analogWrite (dv_right_forw, forw_right_velocity / sk);
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_left_back, LOW);
    digitalWrite (dv_left_forw, LOW);
  }
  server.send(200, "text/plain", "OK");
}
void right_handler() {
  Serial.println("right");
  if (pv == 1) {
    analogWrite (dv_left_forw, forw_left_velocity / sk);
    analogWrite (dv_right_back, back_right_velocity / sk);
    digitalWrite (dv_right_forw, LOW);
    digitalWrite(dv_left_back, LOW);
  } else {
    analogWrite (dv_left_forw, forw_left_velocity / sk);
    digitalWrite (dv_right_forw, LOW);
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_left_back, LOW);
    server.send(200, "text/plain", "OK");
  }
}

void led() {
  Serial.println("led");
  val = !val;
  digitalWrite (LED, val);
  server.send(200, "text/plain", "OK");
}
void pov() {
  Serial.println("pov");
  pv = !pv;
  server.send(200, "text/plain", "OK");
}
void sk1() {
  Serial.println("sk1");
  sk = 2;
  server.send(200, "text/plain", "OK");
}
void sk2() {
  Serial.println("sk2");
  sk = 1;
  server.send(200, "text/plain", "OK");
}
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(dv_left_back, OUTPUT);
  pinMode(dv_right_back, OUTPUT);
  pinMode(dv_right_forw, OUTPUT);
  pinMode(dv_left_forw, OUTPUT);
  digitalWrite(dv_left_back, LOW);
  digitalWrite(dv_right_back, LOW);
  digitalWrite(dv_right_forw, LOW);
  digitalWrite(dv_left_forw, LOW);
  digitalWrite (LED, LOW);
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("WiBot IP = ");
  Serial.println(WiFi.softAPIP());



  server.begin();
  server.on("/stop", stop_handler);
  server.on("/forw", forw_handler);
  server.on("/back", back_handler);
  server.on("/left", left_handler);
  server.on("/right", right_handler);


  server.on("/led", led);
  server.on("/pv", pov);
  server.on("/sp1", sk1);
  server.on("/sp2", sk2);
}


void loop()
{
  server.handleClient();
}
