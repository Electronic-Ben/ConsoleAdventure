#pragma once

#include <string>
#include <unordered_map>
#include <utility>

#include "engine/headers/SelectMenu.h"

class Menu
{
  public:
    bool isOpen = false;

  private:
    int displayWidth;
    std::unordered_map<std::string, SelectMenu> menus;
    std::string display;

  public:
    Menu(int displayW);
    SelectMenu &addMenu(std::string name);
    SelectMenu *getMenu(std::string &name);
    std::string getDisplay();
    void openMenu(std::string const &name);
    void closeMenu(std::string const &name);
    void update();

  private:
    std::string toString();
    bool anyOpen();
};