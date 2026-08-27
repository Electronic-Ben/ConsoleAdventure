#include "engine/headers/Keyboard.h"
#include <Windows.h>

void Keyboard::readInput()
{
    for (int i = 0; i < Key::Count; i++)
    {
        Button &b = keys[i];
        bool nowDown = (GetAsyncKeyState(mapToVK(i)) & 0x8000) != 0;

        b.pressed = !b.down && nowDown;
        b.released = b.down && !nowDown;
        b.down = nowDown;
    }
}

bool Keyboard::keyDown(Key key) const { return keys[key].down; }

bool Keyboard::keyPressed(Key key) const { return keys[key].pressed; }

bool Keyboard::keyReleased(Key key) const { return keys[key].released; }

int Keyboard::mapToVK(int key)
{
    switch (key)
    {
    case Key::W:
        return 'W';
    case Key::A:
        return 'A';
    case Key::S:
        return 'S';
    case Key::D:
        return 'D';
    case Key::Up:
        return VK_UP;
    case Key::Down:
        return VK_DOWN;
    case Key::Left:
        return VK_LEFT;
    case Key::Right:
        return VK_RIGHT;
    case Key::B:
        return 'B';
    case Key::N:
        return 'N';
    default:
        return 0;
    }
}

Button::Button() : down(false), pressed(false), released(false) {}
