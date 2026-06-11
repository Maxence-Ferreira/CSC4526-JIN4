#pragma once
#include "Enemy.h"

class HorseSoldier : public Enemy {
 public:
  HorseSoldier(Path* beginPath);
  ~HorseSoldier() = default;
  void draw(const context& ctx) override;
};
