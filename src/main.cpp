#include <Arduino.h>
#include "TactileBelt.h"
#include "Motor.h"

using namespace DesignHub;

unsigned long lastTick = 0;
unsigned long debounceDelay = 50;

const int pin_Led = 13;
int status_Led = LOW;

TactileBelt *Belt;

void setup()
{
  pinMode(pin_Led, OUTPUT);
  digitalWrite(pin_Led, status_Led);

  Belt = new TactileBelt();

  Serial.begin(57600);

  while (!Serial)
    ;

  Serial.print("You're connected.");
}

void loop()
{
  // read Serial
  // 0=20,0,100&1=0,0,30&7=200,0,255

  // split String
  // parse String
  Belt->update();
  if (Belt->shouldRender())
  {
    Belt->render();
  }
}

void serialEvent()
{
  while (Serial.available())
  {
  }
}
