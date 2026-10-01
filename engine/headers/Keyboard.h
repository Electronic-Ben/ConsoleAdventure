#pragma once

#include <SDL/SDL.h>
#include <array>

#include "engine/headers/KeyState.h"
#include "engine/headers/Keys.h"

enum class KeyState : uint8_t
{
  Up,
  Held,
  Pressed,
  Released
};

class Keyboard
{
private:
  std::array<KeyState, Key::Count> keyStates;

public:
  void update();
  bool keyDown(int keyCode) const;
  bool keyPressed(int keyCode) const;
  bool keyReleased(int keyCode) const;
};
