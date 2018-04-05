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

  void setMotorForce(int motorId, int force)
  {
    _motors.at(motorId)->force = force;
  }

  void setSettings(TactileSettings *settings)
  {
    delete _settings;
    _settings = settings;
  }

  void update()
  {
    if (_settings == nullptr)
    {
      return;
    }

    for (const auto &el : _motors)
    {
      el.second->force = _settings->getForce(el.first);
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
