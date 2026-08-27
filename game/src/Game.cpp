#include "game/headers/Game.h"
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

    screen.moveTo(player.getX(), player.getY());
    screen.update(world);
}

void Game::render()
{
    char activeTile = (player.bumped == ' ') ? player.standing : player.bumped;

    screen.drawToTop(world.getDesc(activeTile) + world.getIntractTxt(activeTile) + '\n');

    screen.drawToBottom(world.getActions());

    screen.drawToBottom("\n " + actionBar.getDisplay());

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

    if (keyboard.keyPressed(Key::N))
    {
        char targetTile = (player.bumped == ' ') ? player.standing : player.bumped;
        int targetX = (player.bumped == ' ') ? player.getX() : player.bumpX;
        int targetY = (player.bumped == ' ') ? player.getY() : player.bumpY;

        switch (targetTile)
        {
        case '%':
            actionBar.set(20, 100, "removing");
            actionBar.setCallback([this, targetX, targetY]() { this->world.setTile(targetX, targetY, '_'); });
            break;
        }
    }

    if (keyboard.keyPressed(Key::B))
    {
        char targetTile = (player.bumped == ' ') ? player.standing : player.bumped;
        int targetX = (player.bumped == ' ') ? player.getX() : player.bumpX;
        int targetY = (player.bumped == ' ') ? player.getY() : player.bumpY;

        // TODO: adjust menu options based on tile and inventory
        // switch (targetTile)
        // {
        // case '%':

        // }
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
