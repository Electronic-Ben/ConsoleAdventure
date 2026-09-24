#pragma once

#include "engine/headers/ItemRegistry.h"
#include <string>
#include <unordered_map>

class ItemStack
{
private:
  std::string name;
  int type;
  int itemCount;

public:
  ItemStack(std::string name, int count = 1);
  int getType();
  int getItemCount() const;
  std::string getName() const;
  void addItem(int count);
  void removeItem(int count);
  bool combineStacks(ItemStack &other);
};