#pragma once
#include "Enemy.h"

class Kamikaze : public Enemy {
 public:
  Kamikaze(Path* beginPath);
  ~Kamikaze() = default;
  virtual void attacking(Tile * targetTile) override;
};
