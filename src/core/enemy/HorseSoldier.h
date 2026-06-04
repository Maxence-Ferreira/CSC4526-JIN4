#pragma once
#include "Enemy.h"

class HorseSoldier : public Enemy {
 public:
  HorseSoldier(double x, double y);
  ~HorseSoldier() = default;
  virtual void attacking(Tile * targetTile) override;
};
