#pragma once
#include "Enemy.h"

class Kamikaze : public Enemy {
 public:
  Kamikaze(Path* beginPath);
  ~Kamikaze() = default;
  virtual Attack* attacking(Building* targetBuilding) override;
  void draw(const context& ctx) override;
};
