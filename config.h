#pragma once
#define MOSTURE_SENSOR_PIN 17
#define SOIL_TEMP_SENSOR_PIN 15

#define LED_STRIP_PIN 35
#define PUMP_PIN 36
#define COOLER_PIN 37
#define HEATER_PIN 38

#define YELLOW_LED_PIN 1
#define RED_LED_PIN 20
#define GREEN_LED_PIN 21

// GPIO 8 (SDA)
// GPIO 9 (SCL)

char *ssid = "iPhone Ann";
char *password = "12345678910";

#define BOT_TOKEN "8127877503:AAGpV7Wk6JFMBG-SFpz3vonvdET0n0ZKUTk"
#define CHAT_ID "922443025"

bool isConnectedMostureSensor = false;
bool isConnectedBme280 = false;
bool isConnectedBh1750 = false;
bool isConnectedDs18b20 = false;

bool heaterState = LOW;
bool coolerState = LOW;
bool lightingState = LOW;
bool pumpState = LOW;
bool automaticModeState = false;

bool redLedState = LOW;
bool greenLedState = LOW;
bool yellowLedState = LOW;

const int AirValue = 590;
const int WaterValue = 360;