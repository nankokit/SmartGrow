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
  setupLeds();

  setupDevices();

  setupWiFi();
  setupTelegram();
}

void loop()
{
  checkConnectsSensors();
  if (!isConnectWiFi())
  {
    setupWiFi();
  }
  loopTelegram();
  delay(500);
}
