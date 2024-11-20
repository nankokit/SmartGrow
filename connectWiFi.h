#include <WiFi.h>
#include "config.h"

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
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        // Serial.println('.');
        Serial.print("Status: ");
        Serial.println(WiFi.status());
        delay(3000);
    }
    Serial.println("Successful connection to WiFi!");
    flash_led(YELLOW_LED_PIN, 3);
    printWifiStatus();
}

void scanWiFi()
{
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
        }
    }
    Serial.println("");
}

void setupWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    scanWiFi();
    initWiFi();
}

bool isConnect()
{
    return WiFi.status() == WL_CONNECTED;
}