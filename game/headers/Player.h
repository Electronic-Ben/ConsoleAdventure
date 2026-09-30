#pragma once

#include "engine/headers/World.h"
#include "engine/headers/Container.h"
#include "engine/headers/Equipment.h"
#include "engine/headers/Tile.h"

class Player
{
private:
  Container inventory;
  Equipment equipment;
  Tile &bumped;

  int x = 0;
  int y = 0;

public:
  Player(int X, int Y);

  void update();
  int getX() const;
  int getY() const;
  bool move(int dx, int dy, const World &world);

private:
};