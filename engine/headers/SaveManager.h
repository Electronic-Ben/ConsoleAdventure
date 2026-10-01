#pragma once

#include "engine/headers/WorldSaver.h"
#include "engine/headers/PlayerSaver.h"
#include "engine/headers/SettingsSaver.h"
#include "engine/headers/ChunkStorage.h"

class SaveManager
{
private:
  WorldSaver worldSaver;
  PlayerSaver playerSaver;
  SettingsSaver settingsSaver;
  ChunkStorage chunkStorage;

public:
  void saveGame();
};