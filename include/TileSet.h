#pragma once

#include <Sprite.h>
#include <iostream>

class TileSet {
private:
  Sprite tileSet;

  int tileWidth;
  int tileHeight;
public:
  TileSet(int tileWidth, int tileHeight, std::string file);

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();
};
