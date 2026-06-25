#include "HX711.h"
#include <WiFi.h>
#include <ThingSpeak.h>

#define HX_DOUT 4
#define HX_SCK 5

#define GREEN_LED 18
#define RED_LED 19
#define BUZZER 21

#define MIN_WEIGHT 10
#define MAX_WEIGHT 40

HX711 scale;
WiFiClient client;

float calibrationFactor = 420.0;

const char* ssid = "Wokwi-GUEST";
const char* password = "";

unsigned long channelID = 3413037;
const char* writeAPIKey = "XUYH2TVD291N111B";

float weight = 0;
int statusCode = 0;
int previousStatus = -1;

void setup() {

  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);

  scale.begin(HX_DOUT, HX_SCK);

  Serial.println("Remove all weight...");
  delay(3000);

  scale.tare();

  Serial.println("Scale Ready!");
  Serial.println("----------------------------");
}

void loop() {

  weight = abs(scale.read()) / calibrationFactor;

  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" kg");

  if (weight < MIN_WEIGHT) {

    statusCode = 1;

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("LOW STOCK ALERT");
  }
  else if (weight > MAX_WEIGHT) {

    statusCode = 2;

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("OVERLOAD ALERT");
  }
  else {

    statusCode = 0;

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    Serial.println("NORMAL");
  }


  if (statusCode != previousStatus) {

    if (statusCode == 1) {
      tone(BUZZER, 1000, 300);
    }

    else if (statusCode == 2) {
      tone(BUZZER, 2000, 300);
    }

    previousStatus = statusCode;
  }


  ThingSpeak.setField(1, weight);
  ThingSpeak.setField(2, statusCode);

  int response = ThingSpeak.writeFields(
    channelID,
    writeAPIKey
  );

  if (response == 200) {
    Serial.println("ThingSpeak Update Successful");
  }
  else {
    Serial.print("ThingSpeak Error: ");
    Serial.println(response);
  }

  Serial.println("----------------------------");

  delay(15000);
}

