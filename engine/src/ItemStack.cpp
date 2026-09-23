#include "engine/headers/ItemStack.h"

ItemStack::ItemStack(std::string name, int count)
    : name(name), itemCount(count), type(ItemRegistry::getItemType(name)) {}

int ItemStack::getItemCount() { return itemCount; }

int ItemStack::getType() { return type; }

std::string ItemStack::getName() { return name; }

void ItemStack::addItem(int count) { itemCount += count; }

void ItemStack::removeItem(int count) { itemCount -= count; }
