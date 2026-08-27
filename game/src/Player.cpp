#include "game/headers/Player.h"

Player::Player(int X, int Y) : x(X), y(Y) {}

void Player::update(const Keyboard &keyboard, World &world)
{
    handleMovement(keyboard, world);
    handleActions(keyboard, world);
}

void Player::handleMovement(const Keyboard &keyboard, const World &world)
{
    bumped = ' ';

    if (moveTimer > 0)
        moveTimer--;

    int dx = 0, dy = 0;

    if ((keyboard.keyPressed(Key::W) || keyboard.keyPressed(Key::Up)) ||
        ((keyboard.keyDown(Key::W) || keyboard.keyDown(Key::Up)) && moveTimer == 0))
        dy--;

    if ((keyboard.keyPressed(Key::S) || keyboard.keyPressed(Key::Down)) ||
        ((keyboard.keyDown(Key::S) || keyboard.keyDown(Key::Down)) && moveTimer == 0))
        dy++;

    if ((keyboard.keyPressed(Key::A) || keyboard.keyPressed(Key::Left)) ||
        ((keyboard.keyDown(Key::A) || keyboard.keyDown(Key::Left)) && moveTimer == 0))
        dx--;

    if ((keyboard.keyPressed(Key::D) || keyboard.keyPressed(Key::Right)) ||
        ((keyboard.keyDown(Key::D) || keyboard.keyDown(Key::Right)) && moveTimer == 0))
        dx++;

    moved = move(dx, dy, world);

    dy = dx && dy ? 0 : dy;

    if (moved)
    {
        moveTimer = moveCooldown;
        if (actionBar.active())
        {
            actionBar.reset();
        }
    }
    else
    {

        bumpX = x + dx;
        bumpY = y + dy;
        bumped = world.getTile(x + dx, y + dy);
    }

    standing = world.getTile(x, y);
}

void Player::handleActions(const Keyboard &keyboard, World &world)
{
    if (actionBar.active() && moved)
    {
        actionBar.reset();
    }

    actionBar.tick();

    if (keyboard.keyPressed(Key::N))
    {
        char targetTile = (bumped == ' ') ? standing : bumped;
        int targetX = (bumped == ' ') ? x : bumpX;
        int targetY = (bumped == ' ') ? y : bumpY;

        switch (targetTile)
        {
        case '%':
            actionBar.set(20, 100, "removing");
            actionBar.setCallback([&world, targetX, targetY]() { world.setTile(targetX, targetY, '_'); });
            break;
        }
    }

    if (keyboard.keyPressed(Key::B))
    {
        char targetTile = (bumped == ' ') ? standing : bumped;
        int targetX = (bumped == ' ') ? x : bumpX;
        int targetY = (bumped == ' ') ? y : bumpY;

        // TODO: adjust menu options based on tile and inventory
        // switch (targetTile)
        // {
        // case '%':

        // }
    }
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

bool Player::getMoved() const { return moved; }