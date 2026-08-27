#include "game/headers/Player.h"

Player::Player(int X, int Y) : x(X), y(Y) {}

void Player::update(const World &world, int dx, int dy)
{
    bumped = ' ';

    if (moveTimer > 0)
        moveTimer--;

    moved = moveTimer <= 0 ? move(dx, dy, world) : false;

    dy = dx && dy ? 0 : dy;

    if (moved)
    {
        moveTimer = moveCooldown;
    }
    else
    {
        bumpX = x + dx;
        bumpY = y + dy;
        bumped = world.getTile(x + dx, y + dy);
    }

    standing = world.getTile(x, y);
}

bool Player::move(int dx, int dy, const World &world)
{
    if (dx == 0 && dy == 0)
        return false;

    bool horizFree = !world.impassable(world.getTile(x + dx, y));
    bool vertFree = !world.impassable(world.getTile(x, y + dy));
    bool diagFree = !world.impassable(world.getTile(x + dx, y + dy));

    if (dx != 0 && dy != 0 && diagFree && (horizFree || vertFree))
    {
        x += dx;
        y += dy;
        return true;
    }

    if (dx != 0 && horizFree)
    {
        x += dx;
        return true;
    }

    if (dy != 0 && vertFree)
    {
        y += dy;
        return true;
    }

    return false;
}

int Player::getX() const { return x; }

int Player::getY() const { return y; }

char Player::getModel() const { return model; }

bool Player::hasMoved() const { return moved; }