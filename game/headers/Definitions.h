#pragma once

#include <vector>

#include "game/headers/ItemDefinition.h"
#include "game/headers/EntityDefinition.h"
#include "game/headers/TileDefinition.h"
#include "game/headers/ActionDefinition.h"

class Definitons
{
private:
  std::vector<ItemDefinition> itemDefs;
  std::vector<EntityDefinition> entityDefs;
  std::vector<TileDefinition> tileDefs;
  std::vector<ActionDefinition> actionDefs;

public:
  ItemDefinition getItemDef();
  EntityDefinition getEntityDef();
  TileDefinition getTileDef();
  ActionDefinition getActionDef();
};