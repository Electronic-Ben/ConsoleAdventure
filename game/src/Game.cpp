#include "game/headers/Game.h"
#include "engine/headers/Keyboard.h"
#include <algorithm>
#include <functional>

Game::Game() : screen(0, 0, 31, 9), player(50, 15), menu(31) {}

void Game::run()
{
    init();

    while (running)
    {
        keyboard.readInput();
        update();
        render();

        Sleep(30);
    }

    exit();
}

void Game::init()
{
    world.setMap(100, 30, getMap());

    screen.init();
    initMenus();
}

void Game::update()
{
    handleActions();
    menu.update();
    screen.moveTo(player.getX(), player.getY());
    screen.update(world);
}

void Game::render()
{
    char activeTile = (player.bumped == ' ') ? player.standing : player.bumped;

    screen.drawToTop(world.getDesc(activeTile) + world.getIntractTxt(activeTile) + '\n');

    screen.drawToBottom(world.getActions());

    if (actionBar.active())
    {
        screen.drawToBottom("\n " + actionBar.getDisplay());
    }

    if (menu.isOpen)
    {
        screen.drawToBottom("\n" + menu.getDisplay());
    }

    if (!(actionBar.active() || menu.isOpen))
        screen.drawToBottom("\n" + screen.blankLine);

    screen.draw(player.getX(), player.getY(), player.getModel());
    screen.render();
}

void Game::initMenus()
{
    auto &buildMenu = menu.addMenu("build");
    buildMenu.addOption("Wall", []() { /*TODO*/ }, false);
    buildMenu.addOption("Door", []() { /*TODO*/ }, false);
    buildMenu.addOption("Bridge", []() { /*TODO*/ }, false);
    buildMenu.addOption("Mine", []() { /*TODO*/ }, false);
    buildMenu.addOption("Furnace", []() { /*TODO*/ }, false);
    buildMenu.addOption("CraftingTable", []() { /*TODO*/ }, false);
    buildMenu.addOption("Chest", []() { /*TODO*/ }, false);
    buildMenu.addOption("Exit", [&buildMenu]() { buildMenu.close(); });
}

void Game::handleActions()
{
    if (actionBar.active() && player.hasMoved())
    {
        actionBar.reset();
    }

    actionBar.tick();

    KeyMap keyMap;

    if (keyboard.keyDown(Key::W) || keyboard.keyDown(Key::Up))
        keyMap.up = true;
    if (keyboard.keyDown(Key::S) || keyboard.keyDown(Key::Down))
        keyMap.down = true;
    if (keyboard.keyDown(Key::A) || keyboard.keyDown(Key::Left))
        keyMap.left = true;
    if (keyboard.keyDown(Key::D) || keyboard.keyDown(Key::Right))
        keyMap.right = true;

    keyMap.waitX = !(keyboard.keyPressed(Key::A) || keyboard.keyPressed(Key::D));
    keyMap.waitY = !(keyboard.keyPressed(Key::W) || keyboard.keyPressed(Key::S));

    player.update(world, keyMap);

    if (keyboard.keyPressed(Key::N))
    {
        char targetTile = (player.bumped == ' ') ? player.standing : player.bumped;
        int targetX = (player.bumped == ' ') ? player.getX() : player.bumpX;
        int targetY = (player.bumped == ' ') ? player.getY() : player.bumpY;

        switch (targetTile)
        {
        case '%':
            actionBar.set(20, 100, "removing", [this, targetX, targetY]() { world.setTile(targetX, targetY, '_'); });
            break;
        }
    }

    if (keyboard.keyPressed(Key::B))
    {
        char targetTile = (player.bumped == ' ') ? player.standing : player.bumped;
        int targetX = (player.bumped == ' ') ? player.getX() : player.bumpX;
        int targetY = (player.bumped == ' ') ? player.getY() : player.bumpY;

        // TODO: adjust menu options based on tile and inventory

        menu.openMenu(std::string("build"));
    }
}

void Game::exit() { screen.showCursor(); }

std::string Game::getMap()
{
    std::string rawMap = R"(
####################################################################################################
#.,..,,.,,,.,.,...,,.,,,.,...,,.,,..,..,,.,,,...,.,.,,..,,.,,,.,,,.,...,.,~~..,,...,,.,..,.,,.,.,.,#
#,,.,,,.,,...,.,..,,..,,.,,..,.,.,,....,..,..,.,,.,..,..,,..,.,.,,..,.,..~~~.,,..,..,.,..,..,.,,.,,#
#.,.,...,,.,,,.,.,.,..,,.,,..,.,...,,,..,,..,..,,,.,.,,..,..,..,,.,,.,,,..,~~~.,....,,,..,,...,.,..#
#..,,..,,.,,,..,..,.,.,,,..,.,.,,..,..,.,..,...,.,.,,,.,,..,..,.,...,,,..,,,~~~~.,,.,.,.,.,.,...,.,#
#,,.,.,..,.,.,,,.,.,..,.,.,,..,.,,.,.,..,,..,,.,.,....,..,,.,..,,.,,.,..,.,..,,~~.,,.,,,...,,.,...,#
#.,.,,,....,,.,..,.,.,...,,,...,,..,.,,..,.,...,,,.,.,,.,...,,.,.,"""".,...,.,.~~,,...,,..,,,.,.,..#
#,.,,.,.,,..,.,..,..,,.,.,...,,..,..,.,..,,.,,,..,.,,...,,,.,Y.Y,"YYY"""",.,.,,~~,.,.,..,..,,.,.,.,#
#..,,.,,,..,,.,.,.,.,..,.,,,.,...,.,,.,,.,.,,,.,..,,...,,.YY,.Y.YY""Y""YY"".,.,,~~..,,.,..,.,,.,,,.#
#,,.,.,..,.,..,,,..,,.,,,..,,.,,.,.,..,.,.,.,..,.,.,.,,,.,,.YY.Y,.YYY"Y"Y",.,..,.~~.,..,,,..,.,,.,,#
#..,.,...""",,,..,.,,.,,.,...,,,.,.,,.,,,..,.,.,.,,.,,,.,.,.,,.,,,.,.,,.,.,,,.,,.,~~..,.,.,...,,..,#
#..,..,."""""".,.,..,..,.,,..,.,..,,,,..,.,.,..,,.,,,.,.,,.,.,,.,.,,.,,..,.,,..,.,~~.,....,,,...,.,#
#,,..,.,.,"""".,..,..,..,.,,.,,,..,..,.,.,,.,.,..,..,..,..,,.,.,,.,.,..,,,..,.,,,..~~.,,,...,,..,,.#
#.,.,..,,...,,.,../^\.,,.,,.,,.,..,.,.,,,..,,...,,.,,,..,,..,.,..,..,,..,,..,,.,.,.~~.,..,.,,.,,.,,#
#,,..,..,.,.,,.,./__.\...,.,.,.,,..,.,..,.,...,,,.,,.,.,,.,,...,..,,..,.,.,.,..,~~~~~,.,,,..,,,.,.,#
#.,..,,..,.,..,./_()%_\/^^^\,..,.,..,,,.,..,.,,..,X.,.,,,...,.,.,.,,.,..,,,~~~~~~~.,,.,,.,,..,...,.#
#.,.,..,.,,.,,./_____,,\___%\,,..,,,.,.,.,,..,.,.,.,..,.,,..,.,.,,..,.,..,~~..,.,,,.,..,.,,,...,,.,#
#.,,,.,.,..,,./_,%%.,___\%___\.,,..,.,.,,.,.,..,..,,..,,...,,.,...,,.,.,..~~,.,.,.,..,.,..,.,...,,.#
#.,,.,.,,.,,,..,,...,,,...,,,..,.,..,.,.,,.,.,..,,..,.,,,..,.,..,,,..,,..~~~,.,.,..,,,,...,..,,.,.,#
#.,..,,.,..,,...,,.,..,,.,..,.,,,...,.,,..,..,..,..,.,,,.,.,,..,.,...,.,~~~,...,..,..,..,.,.,.,..,.#
#.,.,...,..,..,..,.,,,..,,.,,,.,,,..,.,..,.,,.,.,,..,.,..,.,,,.,...,.,.~~..,.,,.,.,..,.,.,,.,..,,..#
#,.,..,,.,.,.,,,..,.,..,.,,,.,.,,..,..,..,,..,..,..,.,.,...,,.,.,.,,.,.~~.,,.,.,..,,..,,,.,,,.,,..,#
#..,,,.,.,.,..,..,.,.,,.,..,,.,.,..,,..,.,.,,..,..,.,.,..,.,.,,.~~~~~~~~~..,..,.,.,,,..,.,.,..,.,..#
#.,..,,...,.,..,.,,,..,,.,.,..,.,,,...,..,..,..,,..,..,,.,.,.~~~~~~~~~~~~~~.,.,.,..,,,/^^^\,,...,.,#
#.,.,.,,.,..,.,,,.,..,,.,,..,.,..,.,.,,.,,.,.,.,,..,.,,.,,.,,.,,,~~~~~~~~~~~.,.,,./^\/__()_\,..,,.,#
#,..,.,.,..,,..,..,,,..,..,.,..,.,.,..,,...,,,.,..,,.,.,.,,.,,.,.,~,.~~~~.,,..,,./%__\,____/\/^^\.,#
#,.,..,,.,.,..,.,.,..,..,.,,,...,.,,,.,..,.,,.,..,,..,,...,.,..,,.~,.,..,.,.,,../_____\%%_/_.\,__\,#
#..,,.,.,,.,,.,..,.,...,..,,.,,,..,.,..,..,..,,..,..,.,,,.,..,.,.~~,.,..,.,,..,/_(),__%__/()_,\%__\#
#..,,.,..,,...,,,..,,..,.,.,,.,.,..,..,,.,,..,..,,,..,.,..,..,..,~.,..,,.,,.,..,..,.,,.,.,,..,,.,,.#
####################################################################################################)";

    // Erase newlines
    std::erase(rawMap, '\n');

    return rawMap;
}
