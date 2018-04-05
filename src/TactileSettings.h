#pragma once

#include "stdafx.h"

namespace DesignHub
{
typedef std::pair<int, std::list<int>> motorIdForcesPair;

class TactileSettings
{
private:
  std::map<int, std::list<int>> _motorForcesPerId;

public:
  // TactileSettings()
  // {
  //   Serial.println("new Settings");
  // }

  void appendForce(int motorId, int force)
  {
    auto result = _motorForcesPerId.insert(motorIdForcesPair(motorId, std::list<int>(1, force)));

    // Motor already exists
    if (result.second == false)
    {
      // The first elem of the pair is an iterator that is a pair<const key_type, mapped_type>.
      // "result.first->second" is the list.
      // "ElemToBeAdded.second" is the input-list.
      // result.first->second.push_back(ElemToBeAdded.second.front());
      result.first->second.push_back(force);
    }

    // Serial.print(" motor: ");
    // Serial.print(result.first->first);
    // Serial.print(" force: ");
    // Serial.println(result.first->second.back());
    // Serial.flush();
  }

  int getForce(int motorId)
  {
    auto result = _motorForcesPerId.find(motorId);
    if (result == _motorForcesPerId.end() || result->second.empty())
    {
      return 0;
    }

    int ret = result->second.front();
    result->second.pop_front();
    return ret;
  }
};
}
