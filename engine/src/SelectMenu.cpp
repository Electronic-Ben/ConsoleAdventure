#include "engine/headers/SelectMenu.h"

SelectMenu::SelectMenu(int displayW) : displayWidth(displayW) {}

void SelectMenu::update() { display = std::move(toString()); }

std::string SelectMenu::toString() {
  std::string str = "";
  str += std::string(displayWidth, '-') + '\n';

  rowLengths.clear();

  int currentLine = 0;
  int charsLeft = displayWidth;
  int index = 0;

  for (const auto &opt : options) {
    if (opt.avalible) {
      if (opt.name.size() > charsLeft) {
        str += '\n';
        currentLine++;
        charsLeft = displayWidth;

        rowLengths.push_back(index - 1);
      }

      if (opt.avalible && index == selection) {
        str += ("[" + opt.name + "]");
      } else {
        str += (" " + opt.name + " ");
      }

      charsLeft -= opt.name.size() + 2;
      index++;
    }
  }

  str += '\n' + std::string(displayWidth, '-') + '\n';

  return str;
}

void SelectMenu::addOption(std::string name, std::function<void()> callback,
                           bool isAvalible) {
  options.emplace_back(std::move(name), std::move(callback), isAvalible);
}

std::string SelectMenu::getDisplay() const { return display; }

void SelectMenu::select() {
  options.at(selection).callback();
  close();
}

void SelectMenu::moveUp() {
  if (selection <= 0)
    return;
}

void SelectMenu::moveDown() { selection++; }

void SelectMenu::moveLeft() { selection--; }

void SelectMenu::moveRight() { selection++; }

int SelectMenu::getRow(int index) {
  for (int i = 0; i < rowLengths.size(); i++) {
    if (rowLengths.at(i) >= index) {
      return i;
    }
  }
  return -1;
}

void SelectMenu::close() { isOpen = false; }

void SelectMenu::open() { isOpen = true; }