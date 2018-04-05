#include "stdafx.h"
#include "Config.h"
#include "TactileBelt.h"
#include "TactileSettings.h"

using namespace DesignHub;

TactileBelt *Belt;
unsigned long nextTick;
int skippedFrames;

String forceCharBuffer = "";
int motorId = 0;
TactileSettings *settings = nullptr;
bool isSettingsReady = false;

/**
 * Establish Connection
 */
void establishContact()
{
  Serial.begin(57600);
  while (!Serial)
    ;

  while (Serial.available() <= 0)
  {
    // send a capital A
    Serial.print('A');
    delay(300);
  }
  Serial.println("\nYou're connected.");
}

/**
 * SerialEvent
 *
 * read Serial
 * 0=20,0,100&1=0,0,30&7=200,0,255\r\n
 */
void mySerialEvent()
{
  if (settings == nullptr)
  {
    settings = new TactileSettings();
  }

  while (Serial.available())
  {
    char inChar = (char)Serial.read();

    switch (inChar)
    {
    case '=':
      // buffer has motorId -> set _motorId
      motorId = forceCharBuffer.toInt();
      forceCharBuffer = "";
      break;
    case '\r':
    case '\n':
      // send TactileSettings
      isSettingsReady = true;

      // clear rest buffer
      if (Serial.peek() == '\n')
      {
        Serial.read();
      }
      // expicit fall through
    case ',':
    case '&':
      // buffer has next force as string
      settings->appendForce(motorId, forceCharBuffer.toInt());
      forceCharBuffer = "";
      break;
    default:
      forceCharBuffer += inChar;
    }
  }
}

/**
 * Setup
 */
void setup()
{
  establishContact();

  Belt = new TactileBelt();
  Belt->addMotor(0, 15);
  Belt->addMotor(1, 16);
  Belt->addMotor(2, 17);
  Belt->addMotor(3, 18);
  Belt->addMotor(4, 12);
  Belt->addMotor(5, 11);
  Belt->addMotor(6, 10);
  Belt->addMotor(7, 9);

  forceCharBuffer.reserve(FORCE_CHAR_BUFFER_SIZE);

  nextTick = millis();
}

/**
 * Loop
 */
void loop()
{
  mySerialEvent();
  skippedFrames = 0;
  while (millis() > nextTick && skippedFrames < MAX_SKIPPEDFRAMES)
  {
    if (isSettingsReady)
    {
      Belt->setSettings(settings);
      isSettingsReady = false;
      settings = nullptr;
    }
    Belt->update();
    nextTick += DEBOUNCEDELAY;
    skippedFrames++;
  }

  Belt->render();
}
