#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define the pins that we will use
#define CAPTEUR 33    // pin DATA du DHT11
#define LED 26

#define DHTPIN  CAPTEUR
#define DHTTYPE DHT11   // pour ton capteur

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  dht.begin();
  Serial.println("DHT11 - Mesure temperature / humidite");

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;   // délai mini entre mesures
}

void loop() {
  // Effectuer une mesure toutes les 5s
  delay(5000);

  sensors_event_t event;

  // Humidité
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Erreur lecture humidite !");
  } else {
    Serial.print("Humidite : ");
    Serial.print(event.relative_humidity);
    Serial.println(" %");
  }

  // Température
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Erreur lecture temperature !");
  } else {
    Serial.print("Temperature : ");
    Serial.print(event.temperature);
    Serial.println(" °C");
  }
}
