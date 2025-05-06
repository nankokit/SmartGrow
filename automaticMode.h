#pragma once
#include "devices.h"
#include "tgCommunication.h"
#include "settings.h"

void checkLightLevel()
{
    uint16_t lightLevel = getLightLevel();
    if (lightLevel < minLightLevel)
    {
        lightingState = HIGH;
        digitalWrite(LED_STRIP_PIN, lightingState);
        bot.sendMessage(CHAT_ID, "Light level is too low (" + String(lightLevel) + " lux) - lighting is ON", "");
    }
    if (lightLevel > maxLightLevel)
    {
        lightingState = LOW;
        digitalWrite(LED_STRIP_PIN, lightingState);
        bot.sendMessage(CHAT_ID, "Light level is too high (" + String(lightLevel) + " lux) - lighting is OFF", "");
    }
}

void checkTemperature()
{
    float tempreture = getTemperature();
    if (tempreture < minTemperature)
    {
        heaterState = HIGH;
        digitalWrite(HEATER_PIN, heaterState);
        highlightHeaterWork();
        bot.sendMessage(CHAT_ID, "Temperature is too low (" + String(tempreture) + " *C) - heater is ON", "");
    }
    if (tempreture > maxTemperature)
    {
        heaterState = LOW;
        digitalWrite(HEATER_PIN, heaterState);
        highlightHeaterWork();
        bot.sendMessage(CHAT_ID, "Temperature is too high (" + String(tempreture) + " *C) - heater is OFF and start ventilation", "");
        if (coolerState == LOW)
        {
            coolerState = LOW;
            digitalWrite(COOLER_PIN, coolerState);
            bot.sendMessage(CHAT_ID, "Temperature is too high (" + String(tempreture) + " *C) - cooler is OFF", "");
        }
    }
}

void checkHumidity()
{
    float humidity = getHumidity();
    if (humidity < minHumidity)
    {
        coolerState = LOW;
        digitalWrite(COOLER_PIN, coolerState);
        bot.sendMessage(CHAT_ID, "Humidity is too low (" + String(humidity) + " %) - cooler is OFF and start watering", "");
        pumpState = HIGH;
        digitalWrite(PUMP_PIN, pumpState);
        delay(duringWatering);
        pumpState = LOW;
        digitalWrite(PUMP_PIN, pumpState);
        bot.sendMessage(CHAT_ID, "Finished watering", "");
    }
    if (humidity > maxHumidity)
    {
        coolerState = HIGH;
        digitalWrite(COOLER_PIN, coolerState);
        pumpState = LOW;
        digitalWrite(PUMP_PIN, pumpState);
        bot.sendMessage(CHAT_ID, "Humidity is too high (" + String(humidity) + " %) - cooler is ON and stop watering", "");
    }
}

void checkSoilMoisture()
{
    float soilMoisture = getSoilMoisturePercent();
    if (soilMoisture < minSoilMoisture)
    {
        pumpState = HIGH;
        digitalWrite(PUMP_PIN, pumpState);
        bot.sendMessage(CHAT_ID, "Soil moisture is too low (" + String(soilMoisture) + " %) - start watering", "");
        delay(duringWatering);
        pumpState = LOW;
        digitalWrite(PUMP_PIN, pumpState);
        bot.sendMessage(CHAT_ID, "Finished watering", "");
    }
    if (soilMoisture > maxSoilMoisture)
    {
        pumpState = LOW;
        digitalWrite(PUMP_PIN, pumpState);
        coolerState = HIGH;
        digitalWrite(COOLER_PIN, coolerState);
        bot.sendMessage(CHAT_ID, "Soil moisture is too high (" + String(soilMoisture) + " %) - stop watering and cooler is ON", "");
    }
}

void checkSoilTemperature()
{
    float soilTemperature = getSoilTemperature();
    if (soilTemperature < minSoilTemperature)
    {
        heaterState = HIGH;
        digitalWrite(HEATER_PIN, heaterState);
        bot.sendMessage(CHAT_ID, "Soil temperature is too low (" + String(soilTemperature) + " *C) - heater is ON", "");
    }
    if (soilTemperature > maxSoilTemperature)
    {
        heaterState = LOW;
        digitalWrite(HEATER_PIN, heaterState);
        bot.sendMessage(CHAT_ID, "Soil temperature is too high (" + String(soilTemperature) + " *C) - heater is OFF", "");
    }
}

void automaticMode()
{
    if (isConnectedBme280)
        checkLightLevel();
    if (isConnectedBh1750)
    {
        checkTemperature();
        checkHumidity();
    }
    if (isConnectedMostureSensor)
        checkSoilMoisture();
    if (isConnectedDs18b20)
        checkSoilTemperature();
}