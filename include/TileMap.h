#pragma once

#include <Component.h>
#include <GameObject.h>
#include <TileSet.h>
#include <vector>
#include <memory>

class TileMap: public Component {
private:
  std::vector<int> tileMatrix;
  std::unique_ptr<TileSet> tileSet;

  int mapWidth;
  int mapHeight;
  int mapDepth;
public:
  TileMap(GameObject& associated, std::string file, TileSet* tileSet);
  
  void Load(std::string file);
  void SetTileSet(TileSet* tileSet);
  int& At(int x, int y, int z = 0);
  void RenderLayer(int layer);
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

  int GetWidth();
  int GetHeight();
  int GetDepth();
};
