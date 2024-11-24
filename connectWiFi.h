#pragma once
#include <WiFi.h>
#include "config.h"
#include "devices.h"

void printWifiStatus()
{
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void initWiFi()
{
    redLedState = HIGH;
    digitalWrite(RED_LED_PIN, redLedState);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        flash_led(RED_LED_PIN, 1, 300);
        Serial.print("Status: ");
        Serial.println(WiFi.status());
        redLedState = HIGH;
        digitalWrite(RED_LED_PIN, redLedState);
    }
    redLedState = LOW;
    digitalWrite(RED_LED_PIN, redLedState);
    greenLedState = HIGH;
    digitalWrite(GREEN_LED_PIN, greenLedState);
    Serial.println("Successful connection to WiFi!");
    printWifiStatus();
}

bool scanWiFi(char *ssid)
{
    bool isFoundSsid = false;
    Serial.println("scan start");
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            delay(10);
            if (!isFoundSsid)
                isFoundSsid = ((WiFi.SSID(i)) == ssid);
        }
    }
    Serial.println("");
    return isFoundSsid;
}

void setupWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    while (!scanWiFi(ssid))
        flash_led(RED_LED_PIN, 5, 100);
    initWiFi();
}

bool isConnectWiFi()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        redLedState = HIGH;
        digitalWrite(RED_LED_PIN, redLedState);
        greenLedState = LOW;
        digitalWrite(GREEN_LED_PIN, greenLedState);
    }
    return WiFi.status() == WL_CONNECTED;
}