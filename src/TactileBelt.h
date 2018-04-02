#pragma once

#include "stdafx.h"
#include "Motor.h"
#include "TactileSettings.h"

namespace DesignHub
{
class TactileBelt
{
private:
  std::map<int, Motor *> _motors;
  TactileSettings *_settings = nullptr;

public:
  bool addMotor(int motorId, int motorPin)
  {
    Motor *tmp = new Motor(motorPin);

    auto result = _motors.insert(std::pair<int, Motor *>(motorId, tmp));

    return result.second;
  }

  void update(TactileSettings *settings)
  {
    if (settings != nullptr)
    {
      delete _settings;
      _settings = settings;
    }
    if (_settings == nullptr)
    {
      return;
    }

    for (const auto &el : _motors)
    {
      int force = _settings->getForce(el.first);
      if (force != -1)
      {
        el.second->force = force;
      }
    }
  }

  void render()
  {
    for (const auto &el : _motors)
    {
      el.second->render();
    }
  }
};
}
