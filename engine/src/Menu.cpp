#include "engine/headers/Menu.h"

Menu::Menu(int displayW) : displayWidth(displayW) {}

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

std::string Menu::toString()
{
    std::string str = "";

    for (const auto &menu : menus)
    {
        if (menu.second.isOpen)
        {
            str += menu.second.getDisplay() + "\n";
        }
    }
    return str;
}

std::string Menu::getDisplay() { return display; }