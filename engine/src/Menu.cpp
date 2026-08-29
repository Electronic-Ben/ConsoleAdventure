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

    for (const auto &pair : menus)
    {
        if (pair.second.isOpen)
        {
            str += pair.first + '\n' + pair.second.getDisplay();
        }
    }
    return str;
}

bool Menu::anyOpen()
{
    for (auto const &pair : menus)
    {
        if (pair.second.isOpen)
        {
            return true;
        }
    }
    return false;
}

std::string Menu::getDisplay() { return display; }

void Menu::update()
{
    for (auto &pair : menus)
    {
        pair.second.update();
    }

    isOpen = anyOpen();

    display = toString();
}

void Menu::openMenu(std::string const &name)
{
    auto it = menus.find(name);
    if (it != menus.end())
    {
        it->second.open();
    }
}

void Menu::closeMenu(std::string const &name)
{
    auto it = menus.find(name);
    if (it != menus.end())
    {
        it->second.close();
    }
}
