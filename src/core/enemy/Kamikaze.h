#pragma once
#include "Enemy.h"

class Kamikaze : public Enemy {
 public:
  Kamikaze(double x, double y);
  ~Kamikaze() = default;
  virtual void attacking(Tile * targetTile) override;
};
