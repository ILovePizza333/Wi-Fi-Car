//к561кп1
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
WiFiServer server(80);

const char* ssid = "kiryshka";// имя  точки доступа которую создаст пульт (англ. буквы и можно несколько цифр)
const char* password = "12345678";// пароль точки доступа(англ. буквы или цифры) не менее 8 символов

int but = D8;// к 13 выводу кп1
int ledPin = 13;
int sensorValue = 0;
int sensorValue2 = 0;
String msg = "";

int start_time = 0;
int current_time = 0;

#define A D14// к 10 выводу кп1
#define B D15// к 9 выводу кп1
void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.begin(115200);
  IPAddress IP = WiFi.softAPIP();
  //Serial.flush();
  Serial.println();
  Serial.print("Server IP is: ");
  Serial.println(IP);

  pinMode (but, INPUT);
  pinMode (A, OUTPUT);
  pinMode (B, OUTPUT);
}
void change(int a, int b) {
  digitalWrite(A, a);
  digitalWrite(B, b);
}
void loop() {
  //start_time = micros();
  sensorValue2 = 0;
  sensorValue = 0;

  change(LOW, LOW);
  if (digitalRead(but) == 0) {
    sensorValue2 = 6;
    sensorValue = 0;
  }

  change(LOW, HIGH);
  if (digitalRead(but) == 0) {
    sensorValue = 9;
    sensorValue2 = 0;
  }
  change(HIGH, LOW);
  if (digitalRead(but) == 0) {
    sensorValue2 = -6;
    sensorValue = 0;
  }
  change(HIGH, HIGH);
  if (digitalRead(but) == 0) {
    sensorValue = -9;
    sensorValue2 = 0;
  }


  //Serial.print("X:");
  // Serial.println(sensorValue);
  // Serial.print("Y:");
  // Serial.println(sensorValue2);
  msg = "";
  WiFiClient client = server.available();
  msg = String(sensorValue, DEC) + " " + String(sensorValue2, DEC);
  // msg= "hello";
  client.print(msg);

  client.print('\n');
  delay(10);
  client.stop();

  //current_time = micros();
 // Serial.println(current_time - start_time);
}
