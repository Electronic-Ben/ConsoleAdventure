#include "engine/headers/World.h"

World::World() {}

void World::setMap(int w, int h, const std::string &newMap)
{
    width = w;
    height = h;
    map.assign(newMap.begin(), newMap.end());
}

char World::getTile(int x, int y) const
{
    int index = toIndex(x, y);
    if (x < 0 || x >= width || y < 0 || y >= height)
        return ' ';
    return map[index];
}

void World::setTile(int x, int y, char newVal)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        map[toIndex(x, y)] = newVal;
        changed = true;
    }
}

std::string World::getDesc(char tile)
{

    std::string desc = " [ ]  ";
    desc[2] = tile;

    switch (tile)
    {
    case ',':
    case '.':
        desc.append("Grass     ");
        break;
    case '"':
        desc.append("Tall Grass");
        break;
    case '#':
        desc.append("Wall      ");
        break;
    case 'X':
        desc.append("Spawn     ");
        break;
    case '|':
    case '-':
        desc.append("Path      ");
        break;
    case '^':
        desc.append("Peak      ");
        break;
    case '_':
    case '\\':
    case '/':
        desc.append("Mountain  ");
        break;
    case '%':
        desc.append("Rock Fall ");
        break;
    case 'T':
        desc.append("Mine      ");
        break;
    case 'Y':
        desc.append("Tree      ");
        break;
    case 'y':
        desc.append("Small Tree");
        break;
    case 'o':
        desc.append("Stump     ");
        break;
    case ')':
    case '(':
        desc.append("Cave      ");
        break;
    case '~':
        desc.append("Water     ");
        break;
    default:
        desc.append("???       ");
    }
    return desc;
}

std::string World::getIntractTxt(char tile)
{
    std::string desc = "  N - ";

    switch (tile)
    {
    case '"':
        desc.append("Gather    ");
        break;
    case ',':
    case '.':
    case 'X':
    case '#':
    case '^':
    case '_':
    case '\\':
    case '/':
        desc.append("          ");
        break;
    case '%':
    case '|':
    case '-':
        desc.append("Remove    ");
        break;
    case 'T':
        desc.append("Mine Ore  ");
        break;
    case 'Y':
        desc.append("Chop Down ");
        break;
    case ')':
    case '(':
        desc.append("Explore   ");
        break;
    case '~':
        desc.append("Fish      ");
        break;
    default:
        desc.append("???       ");
    }

    return desc;
}

std::string World::getActions() { return " B - Build     "; }

bool World::impassable(char symbol) const
{
    switch (symbol)
    {
    case '#':
    case '^':
    case '/':
    case '\\':
    case '%':
    case '~':
        return true;
    default:
        return false;
    }
}

bool World::hasChanged() const { return changed; }

int World::toIndex(int x, int y) const { return (y * width) + x; }

Pos World::fromIndex(int index) const
{
    Pos pos = {index % width, index / width};
    return pos;
}