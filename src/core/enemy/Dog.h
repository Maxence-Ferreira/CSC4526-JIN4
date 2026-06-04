#pragma once
#include "Enemy.h"

class Dog : public Enemy {
 public:
  Dog (double x, double y);
  ~Dog() = default;
  virtual void attacking(Tile * targetTile) override;
};
