#pragma once

#include "stdafx.h"

namespace DesignHub
{
typedef std::pair<int, std::list<int>> motorForcesPair;

class TactileSettings
{
private:
  std::map<int, std::list<int>> _motorForcesPerId;

public:
  // TactileSettings()
  // {
  // }

  void appendForce(int motorId, int force)
  {
    motorForcesPair ElemToBeAdded(motorId, std::list<int>(force));
    // std::pair<std::map<int, std::list<int>>::iterator, bool>
    auto result = _motorForcesPerId.insert(ElemToBeAdded);

    // Motor already exists
    if (result.second == false)
    {
      // The first elem of the pair is an iterator that is a pair<const key_type, mapped_type>.
      // "result.first->second" is the list.
      // "ElemToBeAdded.second" is the input-list.
      result.first->second.push_back(ElemToBeAdded.second.front());
    }
  }

  int getForce(int motorId) {
    auto result = _motorForcesPerId.find(motorId);
    if (result == _motorForcesPerId.end() || result->second.empty())
    {
      return -1;
    }

    auto ret = result->second.front();
    result->second.pop_front();
    return ret;
  }
};
}
