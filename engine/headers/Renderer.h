#include "engine/headers/Camera.h"
#include "engine/headers/TileRenderer.h"
#include "engine/headers/EntityRenderer.h"
#include "engine/headers/UiRenderer.h"
#include "engine/headers/PlayerRenderer.h"

class Renderer
{
private:
  Camera camera;
  TileRenderer tileRenderer;
  EntityRenderer entityRenderer;
  UiRenderer uiRenderer;
  PlayerRenderer playerRenderer;

  std::string display;

public:
  void render();
};