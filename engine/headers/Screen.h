#pragma once

#include "engine/headers/World.h"

class Screen
{
private:
	int x;
	int y;
	int width;
	int height;
	std::string top;
	std::string viewport;
	std::string bottom;
public:
	Screen(int X, int Y, int W, int H);
	void init();
	void update(const World& world);
	void render();
	int toIndex(int x, int y) const;
	void hideCursor();
	void showCursor();
	void draw(int worldX, int worldY, char symbol);
	void drawToTop(const std::string& str);
	void drawToBottom(const std::string& str);
	void moveTo(int X, int Y);
};