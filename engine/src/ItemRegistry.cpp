#include "engine/headers/ItemRegistry.h"

std::unordered_map<int, std::string> ItemRegistry::typeToName;
std::unordered_map<std::string, int> ItemRegistry::nameToType;

int ItemRegistry::nextType = 0;

int ItemRegistry::registerItem(std::string name) {
  int type = nextType++;
  typeToName[type] = name;
  nameToType[name] = type;
  return type;
}

std::string ItemRegistry::getTypeName(int type) { return typeToName[type]; }

int ItemRegistry::getItemType(std::string name) { return nameToType[name]; }
