#pragma once

#include <string>
#include <unordered_map>

class ItemRegistry {
private:
  static std::unordered_map<int, std::string> typeToName;
  static std::unordered_map<std::string, int> nameToType;
  static int nextType;

public:
  static int registerItem(std::string name);
  static std::string getTypeName(int type);
  static int getItemType(std::string name);
};