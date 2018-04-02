#pragma once

#include "stdafx.h"

namespace DesignHub
{
class Motor
{
private:
  const int p;
  int _lastForce = 0;

public:
  int force = 0;

public:
  Motor(int pin) : p(pin)
  {
    pinMode(p, OUTPUT);
  }

  void render()
  {
      if (_lastForce == force)
        return;

      analogWrite(p, force);
      _lastForce = force;
  }
};
}
