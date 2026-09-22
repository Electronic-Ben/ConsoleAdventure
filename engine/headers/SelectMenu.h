#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>

struct menuOption {
  std::string name;
  std::function<void()> callback;
  bool avalible;

  menuOption(std::string label, std::function<void()> func,
             bool isAvalible = true)
      : name(std::move(label)), callback(std::move(func)),
        avalible(isAvalible) {}
};

class SelectMenu {
public:
  bool isOpen = false;

private:
  std::vector<menuOption> options;
  std::string display;
  int displayWidth;
  int selection = 0;
  std::vector<int> rowStarts;

public:
  SelectMenu(int displayW);
  std::string getDisplay() const;
  void select();
  void update();
  void addOption(std::string name, std::function<void()> callback,
                 bool isAvalible = true);
  void close();
  void open();

  void moveDown();
  void moveUp();
  void moveLeft();
  void moveRight();

private:
  std::string toString();
  int getRow(int iindex);
};