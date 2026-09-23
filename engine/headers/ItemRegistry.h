#pragma once

#include <string>
#include <unordered_map>

class ItemRegistry {
private:
  static std::unordered_map<int, std::string> idToName;
  static std::unordered_map<std::string, int> nameToId;
  static int nextID;

public:
  static int registerItem(std::string name);
  static std::string getItemName(int id);
  static int getItemID(std::string name);
};