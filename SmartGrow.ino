#include "devices.h"
#include "tgCommunication.h"
#include "automaticMode.h"

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  setupLightmeter();
  setupBme();
  setupDevices();
  setupTelegram();
}

void printStats()
{
  Serial.println("Stats: ");
  printLightLevel();
  printBmeValues();
  printSoilMoisturePercent();
  Serial.println();
}

void loop()
{
  loopTelegram();
  if (automaticModeState)
  {
    automaticMode();
  }
  delay(500);
}
