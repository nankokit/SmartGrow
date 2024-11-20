#pragma once
#include "devices.h"
#include "tgCommunication.h"

void automaticMode()
{
    uint16_t lightLevel = getLightLevel();
    float tempreture = getTemperature();
    float humidity = getHumidity();
    float soilMoisture = getSoilMoisturePercent();

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
    if (tempreture < minTemperature)
    {
        heaterState = HIGH;
        digitalWrite(HEATER_PIN, heaterState);
        bot.sendMessage(CHAT_ID, "Temperature is too low (" + String(tempreture) + " *C) - heater is ON", "");
        // if (coolerState == HIGH)
        // {
        //     coolerState = LOW;
        //     digitalWrite(COOLER_PIN, coolerState);
        //     bot.sendMessage(CHAT_ID, "Temperature is too low (" + String(tempreture) + " *C) - cooler is OFF", "");
        // }
    }
    if (tempreture > maxTemperature)
    {
        heaterState = HIGH;
        digitalWrite(HEATER_PIN, heaterState);
        bot.sendMessage(CHAT_ID, "Temperature is too high (" + String(tempreture) + " *C) - heater is ON", "");
        // if (coolerState == LOW)
        // {
        //     coolerState = LOW;
        //     digitalWrite(COOLER_PIN, coolerState);
        //     bot.sendMessage(CHAT_ID, "Temperature is too high (" + String(tempreture) + " *C) - cooler is OFF", "");
        // }
    }
    if (humidity < minHumidity)
    {
        coolerState = LOW;
        digitalWrite(COOLER_PIN, coolerState);
        bot.sendMessage(CHAT_ID, "Humidity is too low (" + String(humidity) + " %) - cooler is ON and start watering", "");
        pompState = HIGH;
        digitalWrite(POMP_PIN, pompState);
        delay(duringWatering);
        pompState = LOW;
        digitalWrite(POMP_PIN, pompState);
        bot.sendMessage(CHAT_ID, "Finished watering", "");
    }
    if (humidity > maxHumidity)
    {
        coolerState = HIGH;
        digitalWrite(COOLER_PIN, coolerState);
        pompState = LOW;
        digitalWrite(POMP_PIN, pompState);
        bot.sendMessage(CHAT_ID, "Humidity is too high (" + String(humidity) + " %) - cooler is ON and stop watering", "");
    }
    if (soilMoisture < minSoilMoisture)
    {
        pompState = HIGH;
        digitalWrite(POMP_PIN, pompState);
        bot.sendMessage(CHAT_ID, "Soil moisture is too low (" + String(soilMoisture) + " %) - start watering", "");
        delay(duringWatering);
        pompState = LOW;
        digitalWrite(POMP_PIN, pompState);
        bot.sendMessage(CHAT_ID, "Finished watering", "");
    }
    if (soilMoisture > maxSoilMoisture)
    {
        pompState = LOW;
        digitalWrite(POMP_PIN, pompState);
        coolerState = HIGH;
        digitalWrite(COOLER_PIN, coolerState);
        bot.sendMessage(CHAT_ID, "Soil moisture is too high (" + String(soilMoisture) + " %) - stop watering and cooler is ON", "");
    }
}