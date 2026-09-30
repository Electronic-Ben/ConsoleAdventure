#pragma once

#include <unordered_map>

#include "engine/headers/Keyboard.h"
#include "engine/headers/Controller.h"
#include "engine/headers/Action.h"
#include "engine/headers/ActionState.h"

class Input
{
private:
  Keyboard keyboard;
  Controller controller;
  WindowEvents windowEvents;

  std::unordered_map<Action, ActionState> actionStates;

public:
  Input(); // initalize action states based on enum

  void update();
  void reset();

  bool isActionDown();
  bool isActionPressed();
  bool isActionReleased();
};