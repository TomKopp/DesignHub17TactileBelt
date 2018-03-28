#pragma once

#include <Arduino.h>
#include "Config.h"
#include "Motor.h"

namespace DesignHub
{
class TactileBelt
{
private:
  Motor *motors[MOTORSCOUNT];

  // In milliseconds
  unsigned long lastTick = 0;
  unsigned long debounceDelay = 50;

public:
  TactileBelt()
  {
    motors[0] = new Motor(15);
    motors[1] = new Motor(16);
    motors[2] = new Motor(17);
  }

  void update()
  {
  }

  bool shouldRender()
  {
    if ((millis() - lastTick) > debounceDelay)
    {
      lastTick = millis();
      return true;
    }

    return false;
  }

  void render()
  {
    for (byte i = 0; i < MOTORSCOUNT; i++)
    {
      motors[i]->render();
    }
  }
};
}
