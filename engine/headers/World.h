#pragma once

#include <string>
#include <vector>

#inlcude "engine/headers/Entity.h"
#inlcude "engine/headers/WorldObjects.h"
#inlcude "engine/headers/EntityManager.h"
#inlcude "engine/headers/WorldGenerator.h"
#inlcude "engine/headers/ChunkManager.h"

class World
{
private:
  WorldObjects worldObjects;
  EntityManager entityManager;
  WorldGenerator worldGenerator;
  ChunkManager chunkManager;

  int worldSeed;

public:
  World();

  void update();
  ChunkManager getChunkManager();

  void setMap(int w, int h, const std::string &mapStr);
  char getTile(int x, int y) const;
  void setTile(int x, int y, char newVal);
  std::string getDesc(char tile);
  std::string getIntractTxt(char tile);
  std::string getActions();
  bool hasChanged() const;
  int toIndex(int x, int y) const;
  Pos fromIndex(int index) const;
  bool impassable(char symbol) const;
};
