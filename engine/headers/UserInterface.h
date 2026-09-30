#pragma once

#include <unordered_map>

#include "engine/headers/Menu.h"

class UserInterface
{
private:
  std::unordered_map<MenuId, Menu> menus;

public:
  void update();
  Menu getMenu();
};