#include "engine/headers/Screen.h"
#include <iostream>

void Screen::init() {
  std::cout << "\x1B[2J\x1B[H";
  hideCursor();
  std::cout.flush();
}

Screen::Screen(int X, int Y, int W, int H) : x(X), y(Y), width(W), height(H) {
  // pre-allocate string (width + 1 is for \n)
  viewport.resize((width + 1) * height, ' ');

  for (int i = 0; i < height; i++) {
    viewport[(i * (width + 1)) + width] = '\n';
  }
}

void Screen::update(const World &world) {
  top.clear();
  bottom.clear();

  for (int localX = 0; localX < width; localX++) {
    int worldX = x + localX - (width / 2);
    for (int localY = 0; localY < height; localY++) {
      int worldY = y + localY - (height / 2);
      viewport[toIndex(localX, localY)] = world.getTile(worldX, worldY);
    }
  }
}

void Screen::draw(int worldX, int worldY, char symbol) {
  int localX = worldX - x + (width / 2);
  int localY = worldY - y + (height / 2);

  if (localX >= 0 && localX < width && localY >= 0 && localY < height) {
    viewport[toIndex(localX, localY)] = symbol;
  }
}

void Screen::drawToTop(const std::string &str) { top.append(str); }

void Screen::drawToBottom(const std::string &str) { bottom.append(str); }

void Screen::render() {
  // reset the cursor right before drawing
  std::cout << "\x1B[H";
  std::cout << top;
  std::cout << viewport;
  std::cout << bottom;
  std::cout.flush();
}

void Screen::moveTo(int X, int Y) {
  x = X;
  y = Y;
}

int Screen::toIndex(int x, int y) const { return (y * (width + 1)) + x; }

void Screen::hideCursor() { std::cout << "\x1B[?25l"; }

void Screen::showCursor() { std::cout << "\x1B[?25h"; }