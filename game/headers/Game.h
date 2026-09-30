#pragma once

#include "engine/headers/ConsoleEngine.h"
#include "game/headers/ConsoleAdenture.h"

class Game
{
private:
  Input input;
  ActionHandler actionHandler;
  Player player;
  World world;
  UserInterface ui;
  Renderer renderer;
  Settings settings;
  SaveManager saveManager;

  bool shouldQuit = false;

public:
  Game();

  void run();
  void init();
  void update();
  void exit();

private:
  // std::string getMap();
  // void initMenus();
  // void handleActions();
};