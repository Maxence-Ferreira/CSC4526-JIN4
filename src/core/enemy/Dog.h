#pragma once
#include "Enemy.h"

class Dog : public Enemy {
 public:
  Dog (Path* beginPath);
  ~Dog() = default;
  void draw(const context& ctx) override;
  void resetCooldown() override;
};
