#pragma once

#include "engine/headers/KeyBinds.h"
#include "engine/headers/DisplaySettings.h"
#include "engine/headers/AudioSettings.h"
#include "engine/headers/GameplaySettings.h"

class Settings
{
private:
  KeyBinds keyBinds;
  DisplaySettings displaySettings;
  AudioSettings audioSettings;
  GameplaySettings gameplaySettings;

public:
  void loadSettings();
  void saveSettings();
};