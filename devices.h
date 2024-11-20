#pragma once
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "config.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
BH1750 lightMeter;

void flash_led(int LED_PIN, int number)
{
  pinMode(LED_PIN, OUTPUT);
  for (int i = 0; i < number; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    delay(300);
  }
}

void setupLightmeter()
{
  bool status = lightMeter.begin();
  if (!status)
  {
    Serial.println("Could not find a valid BH1750 sensor");
    while (1)
      ;
  }
}

uint16_t getLightLevel()
{
  uint16_t lux = lightMeter.readLightLevel();
  return lux;
}

void printLightLevel()
{
  uint16_t lux = getLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
}

void setupBme()
{
  bool status;
  status = bme.begin(0x76);
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor");
    while (1)
      ;
  }
}

float getTemperature()
{
  return bme.readTemperature();
}

int getPressure()
{
  return bme.readPressure() / 100.0F;
}

int getHumidity()
{
  return bme.readHumidity();
}

void printBmeValues()
{
  Serial.print("Temperature = ");
  Serial.print(getTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(getPressure());
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(getHumidity());
  Serial.println(" %");
}

int getSoilMoisturePercent()
{
  float soilMoistureValue = analogRead(MOSTURE_SENSOR_PIN);
  int AirValue = 2800;
  int WaterValue = 1000;
  float soilmoisturepercent = 100 - (float)(soilMoistureValue - WaterValue) / (AirValue - WaterValue) * 100;
  return soilmoisturepercent;
}

void printSoilMoisturePercent()
{
  Serial.print("Soil mosture value = ");
  float soilmoisturepercent = getSoilMoisturePercent();
  if (soilmoisturepercent >= 100)
  {
    Serial.println("100 %");
  }
  else if (soilmoisturepercent <= 0)
  {
    Serial.println("0 %");
  }
  else if (soilmoisturepercent > 0 && soilmoisturepercent < 100)
  {
    Serial.print(soilmoisturepercent);
    Serial.println("%");
  }
}

void setupDevices()
{
  pinMode(LED_STRIP_PIN, OUTPUT);
  digitalWrite(LED_STRIP_PIN, LOW);

  pinMode(POMP_PIN, OUTPUT);
  digitalWrite(POMP_PIN, LOW);

  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);

  pinMode(COOLER_PIN, OUTPUT);
  digitalWrite(COOLER_PIN, LOW);
}