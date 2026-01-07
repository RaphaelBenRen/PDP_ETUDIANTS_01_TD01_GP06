#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "esp_sleep.h"

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
  Serial.println("DHT11 - Mesure temperature / humidite (Deep Sleep)");

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

  delay(2000);

  sensors_event_t event;

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Erreur lecture humidite !");
  } else {
    Serial.print("Humidite : ");
    Serial.print(event.relative_humidity);
    Serial.println(" %");
  }

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Erreur lecture temperature !");
  } else {
    Serial.print("Temperature : ");
    Serial.print(event.temperature);
    Serial.println(" °C");
  }

  Serial.println("Je pars en deep sleep pendant 5 secondes...");

  esp_sleep_enable_timer_wakeup(5ULL * 1000000ULL);

  esp_deep_sleep_start();

}

void loop() {
}
