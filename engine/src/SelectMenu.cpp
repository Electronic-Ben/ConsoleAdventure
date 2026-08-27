#include "engine/headers/SelectMenu.h"

SelectMenu::SelectMenu(int displayW) : displayWidth(displayW)
{
}

void SelectMenu::update()
{
  display = toString();
}

std::string SelectMenu::toString()
{
  return "__MENU__";
}

void SelectMenu::addOption(std::function<void()> callback, std::string name)
{
  options.emplace_back(std::move(callback), std::move(name));
}

std::string SelectMenu::getDisplay()
{
  return display;
}

void SelectMenu::select()
{
  options.at(selection).callback();
  close();
}

void SelectMenu::moveSelection(int dx, int dy)
{
  int di = dx + (dy * displayWidth);
  if (selection + di < options.size())
  {
    selection += di;
    update();
  }
}

void SelectMenu::close()
{
  isOpen = false;
}

void SelectMenu::open()
{
  isOpen = true;
}

SelectMenu &Menu::addMenu(std::string name)
{
  auto [it, inserted] = menus.try_emplace(std::move(name), displayWidth);
  return it->second;
}

SelectMenu *Menu::getMenu(std::string &name)
{
  auto it = menus.find(name);
  if (it != menus.end())
  {
    return &(it->second);
  }
  return nullptr;
}