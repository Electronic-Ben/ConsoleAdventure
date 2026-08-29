#pragma once

#include <string>
#include <unordered_map>
#include <utility>

#include "engine/headers/SelectMenu.h"

class Menu
{
  private:
    int displayWidth;
    std::unordered_map<std::string, SelectMenu> menus;
    std::string display;

  public:
    Menu(int displayW);
    SelectMenu &addMenu(std::string name);
    SelectMenu *getMenu(std::string &name);
    std::string getDisplay();
    void openMenu(std::string &name);
    void closeMenu(std::string &name);
    void update();

  private:
    std::string toString();
};