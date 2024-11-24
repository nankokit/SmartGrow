#pragma once
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include "config.h"
#include "devices.h"
#include <WiFi.h>

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

int botRequestDelay = 500;
unsigned long lastTimeBotRan;

void sendStats(String chat_id)
{
    String stats = "Stats:\n";

    stats += isConnectedBh1750 ? ("Light: " + String(getLightLevel()) + " lux \n") : "Could not find a valid BH1750 sensor\n";
    stats += isConnectedBme280 ? ("Temperature: " + String(getTemperature()) + " *C\nPressure: " + String(getPressure()) + " hPa\nHumidity: " + String(getHumidity()) + " %\n") : "Could not find a valid BME280 sensor\n";
    stats += isConnectedMostureSensor ? ("Soil mosture: " + String(getSoilMoisturePercent()) + " %\n") : "Could not find a valid Soil Mosture Sensor\n";

    bot.sendMessage(chat_id, stats, "");
}

void handleNewMessages(int numNewMessages)
{
    Serial.println("handle New Messages ");
    Serial.println(String(numNewMessages));

    for (int i = 0; i < numNewMessages; i++)
    {
        String chat_id = String(bot.messages[i].chat_id);
        if (chat_id != CHAT_ID)
        {
            bot.sendMessage(chat_id, "Unauthorized user", "");
            continue;
        }

        String text = bot.messages[i].text;
        Serial.println(text);

        String from_name = bot.messages[i].from_name;

        if (text == "/automatic_mode_on")
        {
            bot.sendMessage(chat_id, "automatic mode set to ON (sorry, but nothing's going to happen)", "");
            automaticModeState = true;
        }

        if (text == "/automatic_mode_off")
        {
            bot.sendMessage(chat_id, "automatic mode set to OFF (sorry, but nothing's going to happen)", "");
            automaticModeState = false;
        }

        if (text == "/sensors_stats")
        {
            sendStats(chat_id);
        }

        if (text == "/devices_status")
        {
            String status = "Devices status :\n";
            status += "Heater: " + String(heaterState == LOW ? "OFF" : "ON") + "\n";
            status += "Cooler: " + String(coolerState == LOW ? "OFF" : "ON") + "\n";
            status += "Lighting: " + String(lightingState == LOW ? "OFF" : "ON") + "\n";
            status += "Pomp: " + String(pompState == LOW ? "OFF" : "ON") + "\n";
            bot.sendMessage(chat_id, status, "");
        }

        if (text == "/heater_on")
        {
            bot.sendMessage(chat_id, "heater state set to ON", "");
            heaterState = HIGH;
            digitalWrite(HEATER_PIN, heaterState);
            highlightHeaterWork();
        }

        if (text == "/heater_off")
        {
            bot.sendMessage(chat_id, "heater state set to OFF", "");
            heaterState = LOW;
            digitalWrite(HEATER_PIN, heaterState);
            highlightHeaterWork();
        }

        if (text == "/cooler_on")
        {
            bot.sendMessage(chat_id, "cooler state set to ON", "");
            coolerState = HIGH;
            digitalWrite(COOLER_PIN, coolerState);
        }

        if (text == "/cooler_off")
        {
            bot.sendMessage(chat_id, "cooler state set to OFF", "");
            coolerState = LOW;
            digitalWrite(COOLER_PIN, coolerState);
        }

        if (text == "/lighting_on")
        {
            bot.sendMessage(chat_id, "lighting state set to ON", "");
            lightingState = HIGH;
            digitalWrite(LED_STRIP_PIN, lightingState);
        }

        if (text == "/lighting_off")
        {
            bot.sendMessage(chat_id, "lighting state set to OFF", "");
            lightingState = LOW;
            digitalWrite(LED_STRIP_PIN, lightingState);
        }

        if (text == "/pomp_on")
        {
            bot.sendMessage(chat_id, "pomp state set to ON", "");
            pompState = HIGH;
            digitalWrite(POMP_PIN, pompState);
        }

        if (text == "/pomp_off")
        {
            bot.sendMessage(chat_id, "pomp state set to OFF", "");
            pompState = LOW;
            digitalWrite(POMP_PIN, pompState);
        }

        if (text == "/help")
        {
            String help = "Hello, " + from_name + "!\n";
            help += "Use the following commands to control your greenhouse:\n\n";
            help += "/automatic_mode_on and /automatic_mode_off - to use the automatic mode \n";
            help += "/sensors_stats - to request sensors values \n";
            help += "/devices_status - to request devices status\n";
            help += "/heater_on and /heater_off - to control heating\n";
            help += "/cooler_on and /cooler_off - to control ventilation\n";
            help += "/lighting_on and /lighting_off - to control lighting\n";
            help += "/pomp_on and /pomp_off - to control watering\n";
            bot.sendMessage(chat_id, help, "");
        }
    }
}

void setupTelegram()
{
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loopTelegram()
{
    if (millis() > lastTimeBotRan + botRequestDelay)
    {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while (numNewMessages)
        {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        lastTimeBotRan = millis();
    }
}