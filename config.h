#pragma once
#define MOSTURE_SENSOR_PIN 17

#define LED_STRIP_PIN 10
#define POMP_PIN 11
#define COOLER_PIN 12
#define HEATER_PIN 13

#define YELLOW_LED_PIN 4
#define RED_LED_PIN 5
#define GREEN_LED_PIN 6

// GPIO 8 (SDA)
// GPIO 9 (SCL)

char *ssid = "iPhone Ann";
char *password = "12345678910";

#define BOT_TOKEN "8127877503:AAGpV7Wk6JFMBG-SFpz3vonvdET0n0ZKUTk"
#define CHAT_ID "922443025"

bool isConnectedMostureSensor = false;
bool isConnectedBme280 = false;
bool isConnectedBh1750 = false;

bool heaterState = LOW;
bool coolerState = LOW;
bool lightingState = LOW;
bool pompState = LOW;
bool automaticModeState = false;

bool redLedState = LOW;
bool greenLedState = LOW;
bool yellowLedState = LOW;

const int AirValue = 590;
const int WaterValue = 360;