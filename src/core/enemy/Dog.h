#pragma once
#include "Enemy.h"

class Dog : public Enemy {
 public:
  Dog (Path* beginPath);
  ~Dog() = default;
  virtual void attacking(Tile * targetTile) override;
};
