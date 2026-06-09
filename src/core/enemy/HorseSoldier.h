#pragma once
#include "Enemy.h"

class HorseSoldier : public Enemy {
 public:
  HorseSoldier(Path* beginPath);
  ~HorseSoldier() = default;
  virtual void attacking(Tile * targetTile) override;
  void draw(const context& ctx) override;
};
