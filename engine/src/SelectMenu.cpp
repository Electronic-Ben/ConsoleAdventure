#include "engine/headers/SelectMenu.h"

SelectMenu::SelectMenu(int displayW) : displayWidth(displayW) {}

void SelectMenu::update() { display = std::move(toString()); }

std::string SelectMenu::toString()
{
    std::string str = "";
    str += std::string(displayWidth, '-') + '\n';

    int currentLine = 0;
    int charsLeft = displayWidth;
    int index = 0;

    for (const auto &opt : options)
    {
        if (opt.avalible)
        {
            if (opt.name.size() > charsLeft)
            {
                str += '\n';
                currentLine++;
                charsLeft = displayWidth;
            }

            if (opt.avalible && index == selection)
            {
                str += ("[" + opt.name + "]");
            }
            else
            {
                str += (" " + opt.name + " ");
            }

            charsLeft -= opt.name.size() + 2;
            index++;
        }
    }

    str += '\n' + std::string(displayWidth, '-') + '\n';

    return str;
}

void SelectMenu::addOption(std::string name, std::function<void()> callback, bool isAvalible)
{
    options.emplace_back(std::move(name), std::move(callback), isAvalible);
}

std::string SelectMenu::getDisplay() const { return display; }

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

void SelectMenu::close() { isOpen = false; }

void SelectMenu::open() { isOpen = true; }