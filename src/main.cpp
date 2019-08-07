#include <Arduino.h>
#include <ArduinoJson.h>

StaticJsonDocument<200> doc;
#define PIN_ENABLE 8
#define PIN_STEP1 2
#define PIN_STEP2 4
#define DIR1 5
#define DIR2 7


void setup() {
  // Initialize serial port
  pinMode(PIN_ENABLE, OUTPUT);
  pinMode(PIN_STEP1, OUTPUT);
  pinMode(PIN_STEP2, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  Serial.begin(9600);
  while (!Serial) continue;
}
void loop() {
   while (Serial.available() > 0){
    digitalWrite(PIN_ENABLE, LOW);
    DeserializationError error = deserializeJson(doc, Serial);
    if (error) {
      Serial.print("deserializeMsgPack() failed: ");
      Serial.println(error.c_str());
      return;
    }
    long motor1 = doc["motor1"];
    boolean dir1 = doc["dir1"];
    long motor2 = doc["motor2"];
    boolean dir2 = doc["dir2"];
    //long motor3 = doc["motor3"];
    //boolean dir3 = doc["dir3"];
    //long motor4 = doc["motor4"];
    //boolean dir4 = doc["dir4"];

    if (dir1 == 1)
        digitalWrite(DIR1, HIGH);
    else
        digitalWrite(DIR1, LOW);
    for(int i = 0; i < motor1; i++){
        digitalWrite(PIN_STEP1, HIGH);
        delay(10);
        digitalWrite(PIN_STEP1, LOW);
        delay(10);
    }

    if (dir2 == 1)
        digitalWrite(DIR2, HIGH);
    else
        digitalWrite(DIR2, LOW);
    for(int i = 0; i < motor2; i++){
        digitalWrite(PIN_STEP2, HIGH);
        delay(10);
        digitalWrite(PIN_STEP2, LOW);
        delay(10);
    }
    // Print values
    Serial.println(motor1);
    Serial.println(dir1);
    Serial.println(motor2);
    Serial.println(dir2);
    //Serial.println(motor3);
    //Serial.println(dir3);
    //Serial.println(motor4);
    //Serial.println(dir4);

   }
   digitalWrite(PIN_ENABLE, HIGH);
   delay(10);

}
