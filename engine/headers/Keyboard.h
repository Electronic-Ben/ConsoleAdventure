#pragma once

#include <array>

#include "extern/cpp-terminal/terminal.hpp"
#include "extern/cpp-terminal/input.hpp"

enum Key
{
  W,
  A,
  S,
  D,
  Up,
  Down,
  Left,
  Right,
  B,
  N,
  M,

  Count
};

struct Button
{
  bool down;
  bool pressed;
  bool released;

  Button();
};

class Keyboard
{
private:
  std::array<Button, Key::Count> keys;

public:
  void readInput();
  bool keyDown(Key key) const;
  bool keyPressed(Key key) const;
  bool keyReleased(Key key) const;

private:
  int mapToVK(int key);
};
