#include <TileSet.h>
#include <iostream>

TileSet::TileSet(
  int tileWidth,
  int tileHeight,
  std::string file
) : tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight) {
  if (!tileSet.IsOpen()) {
    std::cout << "Error loading tileset: " << file << "\n";
    exit(1);
  }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
  int Line = tileSet.GetHeight() / tileHeight;
  int Column = tileSet.GetWidth() / tileWidth;
  if (index > Line * Column - 1) {
    std::cout << "Error rendering tile: " << index << "\n";
    exit(1);
  }

  tileSet.SetClip(
    (index % Column) * tileWidth,
    (index / Column) * tileHeight,
    tileWidth,
    tileHeight
  );
  tileSet.Render(x, y, tileWidth, tileHeight);
}

int TileSet::GetTileWidth() {
  return tileWidth;
}

int TileSet::GetTileHeight() {
  return tileHeight;
}
