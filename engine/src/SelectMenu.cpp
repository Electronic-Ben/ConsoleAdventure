#include "engine/headers/SelectMenu.h"

SelectMenu::SelectMenu(int displayW) : displayWidth(displayW) {}

void SelectMenu::update() { display = std::move(toString()); }

std::string SelectMenu::toString() {
  std::string str = "";
  str += std::string(displayWidth, '-') + '\n';

  rowStarts.clear();
  rowStarts.push_back(0);

  int currentLine = 0;
  int charsLeft = displayWidth;
  int index = 0;

  for (const auto &opt : options) {
    if (opt.avalible) {
      if (opt.name.size() > charsLeft) {
        str += '\n';
        currentLine++;
        charsLeft = displayWidth;

        rowStarts.push_back(index);
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
  rowStarts.push_back(options.size());

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
  int row = getRow(selection);

  if (row > 0) {
    int col = selection - rowStarts[row];
    int prevRowLen = rowStarts[row] - rowStarts[row - 1];

    if (col >= prevRowLen) {
      col = prevRowLen - 1;
    }
    selection = rowStarts[row - 1] + col;
  }
}

void SelectMenu::moveDown() {
  int row = getRow(selection);

  if (row < rowStarts.size() - 2) {
    int col = selection - rowStarts[row];
    int nextRowLen = rowStarts[row + 2] - rowStarts[row + 1];

    if (col >= nextRowLen) {
      col = nextRowLen - 1;
    }
    selection = rowStarts[row + 1] + col;
  }
}

void SelectMenu::moveLeft() {
  int row = getRow(selection);
  if (row < 0)
    return;
  if (selection > rowStarts.at(row)) {
    selection--;
  }
}

void SelectMenu::moveRight() {
  int row = getRow(selection);
  if (row < 0)
    return;
  if (selection < rowStarts.at(row + 1) - 1) {
    selection++;
  }
}

int SelectMenu::getRow(int index) {
  if (rowStarts.empty()) {
    return -1;
  }

  for (int i = 0; i < rowStarts.size() - 1; i++) {
    if (rowStarts.at(i) > index) {
      return i - 1;
    }
  }

  return rowStarts.size() - 1;
}

void SelectMenu::close() { isOpen = false; }

void SelectMenu::open() { isOpen = true; }