#pragma once
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
BH1750 lightMeter;

OneWire oneWire(SOIL_TEMP_SENSOR_PIN);
DallasTemperature sensors(&oneWire);

void setupLeds()
{
  pinMode(YELLOW_LED_PIN, OUTPUT);
  digitalWrite(YELLOW_LED_PIN, LOW);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, LOW);
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void flash_led(int LED_PIN, int flash_number, int duration)
{
  for (int i = 0; i < flash_number; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(duration);
    digitalWrite(LED_PIN, LOW);
    delay(duration);
  }
}

// GY-302 or BH1750
void setupLightmeter()
{
  bool status = lightMeter.begin();
  if (!status)
  {
    Serial.println("Could not find a valid BH1750 sensor");
    isConnectedBh1750 = false;
  }
  else
    isConnectedBh1750 = true;
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

// BME280
void setupBme()
{
  bool status;
  status = bme.begin(0x76);
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor");
    isConnectedBme280 = false;
  }
  else
    isConnectedBme280 = true;
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

// Soil Mosture Sensor v1.2
void setupSoilMostureSensor()
{
  Serial.println(analogRead(MOSTURE_SENSOR_PIN));
  if (analogRead(MOSTURE_SENSOR_PIN) > 100)
    isConnectedMostureSensor = true;
  else
    Serial.println("Could not find a valid Soil Mosture Sensor");
}

int getSoilMoisturePercent()
{
  float soilMoistureValue = analogRead(MOSTURE_SENSOR_PIN);
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

// DS18B20

void setupDs18b20()
{
  sensors.begin();
  sensors.requestTemperatures();
  if (sensors.getTempCByIndex(0) == -127)
  {
    Serial.println("Could not find a valid DS18B20 sensor");
    isConnectedDs18b20 = false;
  }
  else
    isConnectedDs18b20 = true;
}

float getSoilTemperature()
{
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  return temp;
}

void printSoilTemperature()
{
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
}

void printSensorsValues()
{
  printLightLevel();
  printBmeValues();
  printSoilMoisturePercent();
  printSoilTemperature();
}

void checkConnectsSensors()
{
  if (analogRead(MOSTURE_SENSOR_PIN) < 100 || getSoilMoisturePercent() < 0)
  {
    isConnectedMostureSensor = false;
    Serial.println("Could not find a valid Soil Mosture Sensor");
  }
  else
    isConnectedMostureSensor = true;

  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BME280 sensor");
    isConnectedBme280 = false;
  }
  else
    isConnectedBme280 = true;

  if (!lightMeter.begin())
  {
    Serial.println("Could not find a valid BH1750 sensor");
    isConnectedBh1750 = false;
  }
  else
    isConnectedBh1750 = true;
  sensors.requestTemperatures();
  if (sensors.getTempCByIndex(0) == -127)
  {
    Serial.println("Could not find a valid DS18B20 sensor");
    isConnectedDs18b20 = false;
  }
  else
    isConnectedDs18b20 = true;
}

void highlightHeaterWork()
{
  if (heaterState == LOW)
  {
    yellowLedState = LOW;
    digitalWrite(YELLOW_LED_PIN, yellowLedState);
  }
  else
  {
    yellowLedState = HIGH;
    digitalWrite(YELLOW_LED_PIN, yellowLedState);
  }
}

// setup output pins
void setupDevices()
{
  pinMode(LED_STRIP_PIN, OUTPUT);
  digitalWrite(LED_STRIP_PIN, LOW);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);

  pinMode(COOLER_PIN, OUTPUT);
  digitalWrite(COOLER_PIN, LOW);
}