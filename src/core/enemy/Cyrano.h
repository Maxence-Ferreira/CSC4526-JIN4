#pragma once
#include "Enemy.h"

class Cyrano : public Enemy {
 public:
  Cyrano(Path* beginPath);
  ~Cyrano() = default;
  virtual void attacking(Tile* targetTile) override;
};
