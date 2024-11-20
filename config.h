#pragma once
#define MOSTURE_SENSOR_PIN 17
#define LED_STRIP_PIN 5
#define POMP_PIN 6
#define HEATER_PIN 15
#define COOLER_PIN 7

#define YELLOW_LED_PIN 4
#define RED_LED_PIN 4
#define GREEN_LED_PIN 4

// GPIO 8 (SDA)
// GPIO 9 (SCL)

char *ssid = "iPhone Ann";
char *password = "12345678910";

#define BOT_TOKEN "8127877503:AAGpV7Wk6JFMBG-SFpz3vonvdET0n0ZKUTk"
#define CHAT_ID "922443025"

bool heaterState = LOW;
bool coolerState = LOW;
bool lightingState = LOW;
bool pompState = LOW;
bool automaticModeState = false;