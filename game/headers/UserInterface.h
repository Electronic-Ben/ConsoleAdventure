#pragma once

#include <unordered_map>

#include "engine/headers/Menu.h"
#include "engine/headers/MenuId.h"

class UserInterface
{
private:
  std::unordered_map<MenuId, Menu> menus;
  HeadsUpDisplay hud;

  bool menuOpen = false;

public:
  void update();
  Menu getMenu();
};