#pragma once

#include <string>
#include <vector>

struct Pos
{
  public:
    int x, y;

    Pos(int X, int Y) : x(X), y(Y) {}
};

class World
{
  private:
    int width = 0;
    int height = 0;
    bool changed = true;
    std::vector<char> map;

  public:
    World();

    void setMap(int w, int h, const std::string &mapStr);
    char getTile(int x, int y) const;
    void setTile(int x, int y, char newVal);
    std::string getDesc(char tile);
    std::string getIntractTxt(char tile);
    std::string getActions();
    bool hasChanged() const;
    int toIndex(int x, int y) const;
    Pos fromIndex(int index) const;
    bool impassable(char symbol) const;
};
