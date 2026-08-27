#pragma once

#include "engine/headers/Keyboard.h"
#include "engine/headers/ProgressBar.h"
#include "engine/headers/World.h"

class Player
{
  public:
    char bumped = ' ';
    char standing = ' ';
    int bumpX = 0;
    int bumpY = 0;
    ProgressBar actionBar;

  private:
    int x = 0;
    int y = 0;
    char model = '@';
    int moveCooldown = 3;
    int moveTimer = 0;
    bool moved = false;

  public:
    Player(int X, int Y);
    void update(const Keyboard &keyboard, World &world);
    int getX() const;
    int getY() const;
    char getModel() const;
    bool getMoved() const;

  private:
    void handleMovement(const Keyboard &keyboard, const World &world);
    bool move(int dx, int dy, const World &world);
    void handleActions(const Keyboard &keyboard, World &world);
};