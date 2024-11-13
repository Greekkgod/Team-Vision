#include <Servo.h>

Servo solarServo;
Servo rainServo;

const int LDRLeft = A0;
const int LDRRight = A1;
const int rainSensor = A2;
const int relayPin = 11;

int relayState = LOW;
unsigned long previousMillis = 0;
const long onInterval = 30000; 
const long offInterval = 5000; 

void setup() {

  solarServo.attach(9);
  rainServo.attach(10);

  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayState);

  solarServo.write(90); 
  rainServo.write(0);   

  Serial.begin(9600);
}

void loop() {
  
  int leftLDRValue = analogRead(LDRLeft);
  int rightLDRValue = analogRead(LDRRight);
  int threshold = 20;  // Adjust sensitivity

  if (abs(leftLDRValue - rightLDRValue) > threshold) {
    if (leftLDRValue > rightLDRValue) {
      solarServo.write(solarServo.read() + 1); 
    } else {
      solarServo.write(solarServo.read() - 1); 
    }
  }

  // Rain detection
  int rainValue = analogRead(rainSensor);
  if (rainValue > 500) { 
    rainServo.write(90);  
  } else {
    rainServo.write(0);  
  }

 
  unsigned long currentMillis = millis();
  if (relayState == LOW && currentMillis - previousMillis >= offInterval) {
    relayState = HIGH;
    previousMillis = currentMillis;
    digitalWrite(relayPin, relayState);
  }
  else if (relayState == HIGH && currentMillis - previousMillis >= onInterval) {
    relayState = LOW;
    previousMillis = currentMillis;
    digitalWrite(relayPin, relayState);
  }
}
