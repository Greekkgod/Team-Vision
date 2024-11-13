#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SUCHIR";     
const char* password = "12345678900"; 


const int buzzerPin1 = 13;
const int buzzerPin2 = 14;
const int buzzerPin3 = 25;
const int buzzerPin4 = 32;
const int relayPin1 = 26;
const int relayPin2 = 27;

bool buzzerState1 = false;
bool buzzerState2 = false;
bool buzzerState3 = false;
bool buzzerState4 = false;
bool relayState1 = false;
bool relayState2 = false;

WebServer server(80); 


void toggleBuzzer1() {
  buzzerState1 = !buzzerState1;
  digitalWrite(buzzerPin1, buzzerState1 ? HIGH : LOW);
  server.send(200, "text/html", createHTML());
}

void toggleBuzzer2() {
  buzzerState2 = !buzzerState2;
  digitalWrite(buzzerPin2, buzzerState2 ? HIGH : LOW);
  server.send(200, "text/html", createHTML());
}

void toggleBuzzer3() {
  buzzerState3 = !buzzerState3;
  digitalWrite(buzzerPin3, buzzerState3 ? HIGH : LOW);
  server.send(200, "text/html", createHTML());
}

void toggleBuzzer4() {
  buzzerState4 = !buzzerState4;
  digitalWrite(buzzerPin4, buzzerState4 ? HIGH : LOW);
  server.send(200, "text/html", createHTML());
}

void toggleRelay1() {
  relayState1 = !relayState1;
  digitalWrite(relayPin1, relayState1 ? HIGH : LOW);
  server.send(200, "text/html", createHTML());
}

void toggleRelay2() {
  relayState2 = !relayState2;
  digitalWrite(relayPin2, relayState2 ? HIGH : LOW);
  server.send(200, "text/html", createHTML());
}


String createHTML() {
  String html = "<html><body style='text-align:center;'>";
  html += "<h1>ESP32 Component Control</h1>";


  html += "<form action='/toggleBuzzer1' method='POST'><input type='submit' style='padding:20px;font-size:20px;' value='";
  html += buzzerState1 ? "Turn OFF Buzzer 1" : "Turn ON Buzzer 1";
  html += "'></form><br>";

  html += "<form action='/toggleBuzzer2' method='POST'><input type='submit' style='padding:20px;font-size:20px;' value='";
  html += buzzerState2 ? "Turn OFF Buzzer 2" : "Turn ON Buzzer 2";
  html += "'></form><br>";

  html += "<form action='/toggleBuzzer3' method='POST'><input type='submit' style='padding:20px;font-size:20px;' value='";
  html += buzzerState3 ? "Turn OFF Buzzer 3" : "Turn ON Buzzer 3";
  html += "'></form><br>";

  html += "<form action='/toggleBuzzer4' method='POST'><input type='submit' style='padding:20px;font-size:20px;' value='";
  html += buzzerState4 ? "Turn OFF Buzzer 4" : "Turn ON Buzzer 4";
  html += "'></form><br>";

  html += "<form action='/toggleRelay1' method='POST'><input type='submit' style='padding:20px;font-size:20px;' value='";
  html += relayState1 ? "Turn OFF Relay 1" : "Turn ON Relay 1";
  html += "'></form><br>";

  html += "<form action='/toggleRelay2' method='POST'><input type='submit' style='padding:20px;font-size:20px;' value='";
  html += relayState2 ? "Turn OFF Relay 2" : "Turn ON Relay 2";
  html += "'></form>";

  html += "</body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);


  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(buzzerPin3, OUTPUT);
  pinMode(buzzerPin4, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);


  digitalWrite(buzzerPin1, LOW);
  digitalWrite(buzzerPin2, LOW);
  digitalWrite(buzzerPin3, LOW);
  digitalWrite(buzzerPin4, LOW);
  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin2, LOW);


  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", createHTML());
  });
  server.on("/toggleBuzzer1", HTTP_POST, toggleBuzzer1);
  server.on("/toggleBuzzer2", HTTP_POST, toggleBuzzer2);
  server.on("/toggleBuzzer3", HTTP_POST, toggleBuzzer3);
  server.on("/toggleBuzzer4", HTTP_POST, toggleBuzzer4);
  server.on("/toggleRelay1", HTTP_POST, toggleRelay1);
  server.on("/toggleRelay2", HTTP_POST, toggleRelay2);

  server.begin(); 
}

void loop() {
  server.handleClient(); 
}
