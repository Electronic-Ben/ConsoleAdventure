#pragma once

#include "game/headers/Player.h"

class ActionHandler
{
public:
  void handleActions(Player player, ); // get all needed references and include them

private:
  void handlePlayerActions();
  void handleEntityActions();
  void handlePlayerActions();
  void handleGlobalActions();
  void handleUiActions();
};