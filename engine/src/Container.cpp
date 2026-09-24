#include "engine/headers/Container.h"

Container::Container(int capacity) : capacity(capacity) {}

void Container::update()
{
  display = toString();
}

void Container::removeEmptyStacks()
{
  for (auto it = contents.begin(); it != contents.end();)
  {
    if (it->getItemCount() == 0)
    {
      it = contents.erase(it);
      return;
    }
    else
    {
      ++it;
    }
  }
}

int Container::getCapacity() { return capacity; }

int Container::getFreeSlots() { return capacity - contents.size(); }

bool Container::addItem(std::string name, int count)
{
  if (count <= 0)
    return true;

  for (auto &item : contents)
  {
    if (item.getName() == name)
    {
      item.addItem(count);
      return true;
    }
  }

  return false;
}

bool Container::removeItem(std::string name, int count)
{
  if (count <= 0)
    return true;

  for (auto &item : contents)
  {
    if (item.getName() == name)
    {
      item.removeItem(count);
      return true;
    }
  }

  return false;
}

bool Container::hasItem(std::string name)
{
  for (auto &item : contents)
  {
    if (item.getName() == name)
      return true;
  }

  return false;
}

int Container::getItemCount(std::string name)
{
  for (auto &item : contents)
  {
    if (item.getName() == name)
      return item.getItemCount();
  }

  return 0;
}

std::string Container::getDisplay()
{
  return display;
}

std::string Container::toString()
{
  std::string str;

  int maxLen = 0;
  for (const auto &item : contents)
  {
    int numLen = numLength(item.getItemCount());
    if (numLen > maxLen)
      maxLen = numLen;
  }

  for (int i = 0; i < contents.size(); i++)
  {
    const ItemStack &item = contents[i];

    if (i == selected)
    {
      str += "[" + item.getName() + "]";
    }
    else
    {
      str += " " + item.getName() + " ";
    }

    str += "  (" + std::to_string(item.getItemCount()) + ")";
  }

  return str;
}

int Container::numLength(int num)
{
  int count = 0;
  while (num > 0)
  {
    num /= 10;
    count++;
  }
  return count;
}