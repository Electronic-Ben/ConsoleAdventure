#pragma once

#include "engine/headers/ConsoleEngine.h"
#include "game/headers/ConsoleAdenture.h"

class Game
{
  private:
    bool running = true;

    Keyboard keyboard;
    World world;
    Screen screen;
    Player player;
    Menu menu;

  public:
    void run();
    void init();
    void update();
    void render();
    void exit();

    Game();

  private:
    std::string getMap();
    void initMenus();
};