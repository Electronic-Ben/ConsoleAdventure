#pragma once

#include "engine/headers/ItemStack.h"
#include <vector>

class Container {
private:
  std::vector<ItemStack> contents;
  int capacity;

public:
  Container(int capacity);

  bool addItem(std::string name, int count = 1);
  bool removeItem(std::string name, int count = 1);
  bool hasItem(std::string name);
  int getItemCount(std::string name);
  int getFreeSlots();
  int getCapacity();
  void removeEmptyStacks();
};