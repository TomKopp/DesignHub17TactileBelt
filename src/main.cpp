#include "stdafx.h"
#include "Config.h"
#include "TactileBelt.h"
#include "TactileSettings.h"

using namespace DesignHub;

TactileBelt *Belt;
unsigned long nextTick = millis();
int skippedFrames;

/**
 * Setup
 */
void setup()
{
  Belt = new TactileBelt();
  Belt->addMotor(0, 15);
  Belt->addMotor(1, 16);
  Belt->addMotor(2, 17);

  Serial.begin(57600);

  while (!Serial)
    ;

  Serial.print("You're connected.");
}

/**
 * Loop
 */
void loop()
{
  // read Serial
  // 0=20,0,100&1=0,0,30&7=200,0,255

  // split String
  // parse String

  skippedFrames = 0;
  while (millis() > nextTick && skippedFrames < MAX_SKIPPEDFRAMES)
  {
    // new TactileSettings()
    Belt->update(nullptr);

    nextTick += DEBOUNCEDELAY;
    skippedFrames++;
  }

  Belt->render();
}

/**
 * SerialEvent
 */
void serialEvent()
{
  while (Serial.available())
  {
  }
}
