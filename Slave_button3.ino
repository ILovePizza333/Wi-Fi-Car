#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
const char* ssid = "kiryshka";// имя  точки доступа которую вписали пульт
const char* password = "12345678";// пароль точки доступа который вписали пульт
const char* host = "192.168.4.1";
int var = 0;
int X;
int Y;
int u = 200;
String data;
String dataX;
String dataY;
int start_time = 0;
int current_time = 0;

WiFiServer server(80);

#define LED D13
#define dv_left_forv D3
#define dv_left_back D11
#define dv_right_forv D10
#define dv_right_back D4

void setup() {
  int count = 0;
  Serial.begin(115200);
  delay(10);
  //Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  Serial.println();
  pinMode(LED, OUTPUT);
  pinMode(dv_left_back, OUTPUT);
  pinMode(dv_right_back, OUTPUT);
  pinMode(dv_right_forv, OUTPUT);
  pinMode(dv_left_forv, OUTPUT);
  digitalWrite(dv_left_back, LOW);
  digitalWrite(dv_right_back, LOW);
  digitalWrite(dv_right_forv, LOW);
  digitalWrite(dv_left_forv, LOW);
  digitalWrite (LED, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(dv_left_back, LOW);
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_right_forv, LOW);
    digitalWrite(dv_left_forv, LOW);
    delay(1000);
    Serial.print(".");
    count++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Time for connection(s): ");
  Serial.print(count);
  Serial.println();
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
}

void loop() {
//start_time = micros();
  WiFiClient client;
  

  if ((client.connect(host, 80))) {
    // Serial.println("Connected");
    // Serial.print(host);
    // Serial.println();
  }


  data = client.readStringUntil('\n');
  // хотел повысить скорость но эта строчка не дает


  //  Serial.println(data);
  dataX = data[0];

  if (data[1] != ' ') {
    dataX += data[1];
  }

  if (data[2] != ' ') {
    dataY = data[2];
  }
  if (data[3] != ' ') {
    dataY += data[3];
  }
  if (data[4] != ' ') {
    dataY += data[4];
  }

  X = dataX.toInt();
  Y = dataY.toInt();
  // Serial.println(X);
  // Serial.println(Y);


  if (X == 0 && Y == 0) {
    digitalWrite(dv_right_forv, LOW);
    digitalWrite(dv_left_forv, LOW);
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_left_back, LOW);
  }

  if (Y > 0 ) {
    //   Serial.println("forw");
    analogWrite (dv_left_forv, 900 );
    analogWrite (dv_right_forv, 1000 );
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_left_back, LOW);
  }
  if (Y < 0 ) {
    //  Serial.println("back");
    analogWrite (dv_left_back, 900 );
    analogWrite (dv_right_back, 1000 );
    digitalWrite(dv_right_forv, LOW);
    digitalWrite(dv_left_forv, LOW);
  }
  if ( X < 0) {
    // Serial.println("left");
    analogWrite (dv_right_forv, 1000 );
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_left_back, LOW);
    digitalWrite (dv_left_forv, LOW);
  }
  if ( X > 0) {
    // Serial.println("right");
    analogWrite (dv_left_forv, 1000 );
    digitalWrite (dv_right_forv, LOW);
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_left_back, LOW);
  }

  if (data == "hello") {
    var = !var;
    digitalWrite(D13, var);
  }
 //     current_time = micros();
 //  Serial.println(current_time - start_time);
}
