#pragma once

#include "engine/headers/World.h"

class Player
{
  public:
    char bumped = ' ';
    char standing = ' ';
    int bumpX = 0;
    int bumpY = 0;

  private:
    int x = 0;
    int y = 0;
    char model = '@';
    int moveCooldown = 3;
    int moveTimer = 0;
    bool moved = false;

  public:
    Player(int X, int Y);
    void update(const World &world, int dx, int dy);
    int getX() const;
    int getY() const;
    char getModel() const;
    bool hasMoved() const;

  private:
    bool move(int dx, int dy, const World &world);
};