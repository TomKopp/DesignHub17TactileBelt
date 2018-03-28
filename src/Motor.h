#pragma once

#include <Arduino.h>

namespace DesignHub
{
class Motor
{
private:
  const int p;

public:
  bool active = false;
  char force = 0;

public:
  Motor(int pin) : p(pin)
  {
    pinMode(p, OUTPUT);
  }

  void render()
  {
    if (active)
    {
      // digitalWrite(p, HIGH);
      analogWrite(p, force);
    }
    else
    {
      // digitalWrite(p, LOW);
      analogWrite(p, 0);
    }
  }
};
}
