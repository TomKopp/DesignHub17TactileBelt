#pragma once

#include <Arduino.h>
#include <map>
#include <list>

namespace DesignHub
{
typedef std::pair<byte, std::list<int>> motorForcesPair;

class TactileSettings
{
private:
  std::map<byte, std::list<int>> motorForcesPerId;

public:
  // TactileSettings()
  // {
  // }

  void appendForce(byte motorId, int force)
  {
    motorForcesPair ElemToBeAdded(motorId, std::list<int>(force));
    // std::pair<std::map<byte, std::list<int>>::iterator, bool>
    auto result = motorForcesPerId.insert(ElemToBeAdded);

    // Motor already exists
    if (result.second == false)
    {
      // The first elem of the pair is an iterator that is a pair<const key_type, mapped_type>.
      // "result.first->second" is the list.
      // "ElemToBeAdded.second" is the input-list.
      result.first->second.push_back(ElemToBeAdded.second.front);
    }
  }
};
}
