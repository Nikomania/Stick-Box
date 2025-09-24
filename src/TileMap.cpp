#include <TileMap.h>
#include <GameObject.h>
#include <TileSet.h>
#include <Camera.h>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

TileMap::TileMap(
  GameObject& associated,
  std::string file,
  TileSet* tileSet
) : Component(associated), tileSet(tileSet) {
  Load(file);
}

void TileMap::Load(std::string file) {
  std::ifstream tileMapFile(file);
  if (!tileMapFile.is_open()) {
    std::cout << "Error: could not open file " << file << std::endl;
    exit(1);
  }

  std::string matrixData;
  if (!std::getline(tileMapFile, matrixData)) {
    std::cout << "Error: could not read matrix data from file " << file << std::endl;
    exit(1);
  }

  std::stringstream ss(matrixData);

  char comma;
  ss >> mapWidth >> comma >> mapHeight >> comma >> mapDepth;

  tileMatrix.clear();
  for (int layer = 0; layer < mapDepth; layer++) {
    std::string tileLineData;
    std::getline(tileMapFile, tileLineData);
    for (int i = 0; i < mapHeight; i++) {
      std::getline(tileMapFile, tileLineData);
      std::stringstream ss(tileLineData);

      int tile;
      for (int j = 0; j < mapWidth; j++) {
        ss >> tile;

        tileMatrix.push_back(tile);
        if (ss.peek() == ',') {
          ss.ignore();
        }
      }
    }
  }

  tileMapFile.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
  this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
  return tileMatrix.at(
    x + 
    y * mapWidth + 
    z * mapWidth * mapHeight
  );
}

void TileMap::RenderLayer(int layer) {
  if (layer < 0 || layer >= mapDepth) {
    std::cout << "Error: invalid layer " << layer << std::endl;
    exit(1);
  }

  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      tileSet->RenderTile(
        At(x, y, layer),
        x * tileSet->GetTileWidth() + associated.box.x + (layer == 1 ? 0 : Camera::pos.x * 0.1),
        y * tileSet->GetTileHeight() + associated.box.y + (layer == 1 ? 0 : Camera::pos.y * 0.1)
      );
    }
  }
}

void TileMap::Start() {}

void TileMap::Update(float dt) {}

void TileMap::Render() {
  for (int z = 0; z < mapDepth; z++) {
    RenderLayer(z);
  }
}

bool TileMap::Is(std::string type) {
  return type == "TileMap";
}

int TileMap::GetWidth() {
  return mapWidth;
}

int TileMap::GetHeight() {
  return mapHeight;
}

int TileMap::GetDepth() {
  return mapDepth;
}
