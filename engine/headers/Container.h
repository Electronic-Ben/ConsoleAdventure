#pragma once

#include "engine/headers/ItemStack.h"
#include <vector>

class Container
{
private:
  std::vector<ItemStack> contents;
  int capacity;
  std::string display;
  int displayWidth;
  int selected = 0;

public:
  Container(int dispW, int capacity);

  bool addItem(std::string name, int count = 1);
  bool removeItem(std::string name, int count = 1);
  bool hasItem(std::string name);
  int getItemCount(std::string name);
  int getFreeSlots();
  int getCapacity();
  void removeEmptyStacks();
  std::string getDisplay();
  void update();

private:
  std::string toString();
  int numLength(int mun);
};