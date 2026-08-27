#pragma once

#include <array>

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
