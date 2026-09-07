#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>

#include "engine/headers/SelectMenu.h"

class Menu
{
  public:
    bool isOpen = false;
    int lines = 0;
    std::string activeMenu;

  private:
    int displayWidth;
    std::unordered_map<std::string, SelectMenu> menus;
    std::string display;

  public:
    Menu(int displayW);
    SelectMenu &addMenu(std::string name);
    SelectMenu *getMenu(std::string const &name);
    std::string getDisplay();
    void openMenu(std::string const &name);
    void closeMenu(std::string const &name);
    void update();
    bool anyOpen();
    void select();

  private:
    std::string toString();
};