#include "devices.h"
#include "tgCommunication.h"
#include "automaticMode.h"
#include "connectWiFi.h"

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  setupLightmeter();
  setupBme();
  setupSoilMostureSensor();
  setupDs18b20();

  setupLeds();

  setupDevices();

  setupWiFi();
  setupTelegram();
}

void loop()
{
  checkConnectsSensors();
  printSensorsValues();
  if (automaticModeState)
    automaticMode();
  if (!isConnectWiFi())
  {
    setupWiFi();
  }

  loopTelegram();
  delay(500);
}
