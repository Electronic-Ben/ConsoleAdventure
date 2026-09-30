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
};
