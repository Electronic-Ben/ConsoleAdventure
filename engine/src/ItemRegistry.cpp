#include "engine/headers/ItemRegistry.h"

std::unordered_map<int, std::string> ItemRegistry::idToName;
std::unordered_map<std::string, int> ItemRegistry::nameToId;

int ItemRegistry::nextID = 0;

int ItemRegistry::registerItem(std::string name) {
  int id = nextID++;
  idToName[id] = name;
  nameToId[name] = id;
  return id;
}

std::string ItemRegistry::getItemName(int id) { return idToName[id]; }

int ItemRegistry::getItemID(std::string name) { return nameToId[name]; }
