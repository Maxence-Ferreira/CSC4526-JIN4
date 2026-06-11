#pragma once
#include "Enemy.h"

class FirearmSoldier : public Enemy {
 public:
  FirearmSoldier(Path* beginPath);
  ~FirearmSoldier() = default;
  void draw(const context& ctx) override;
};
