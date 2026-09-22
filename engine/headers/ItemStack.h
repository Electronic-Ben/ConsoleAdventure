#pragma once

#include <string>
#include <unordered_map>

class ItemStack
{
private:
  static std::unordered_map<int, std::string> itemReg;

  std::string name;
  int id;
  int maxStack = 50;
  int contents = 0;

public:
  static int getItemID(std::string name);
  static int getItemName(int itemId);
  static void registerItem(std::string name);
};