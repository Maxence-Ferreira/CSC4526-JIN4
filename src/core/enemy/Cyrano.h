#pragma once
#include "Enemy.h"

class Cyrano : public Enemy {
 public:
  Cyrano(Path* beginPath);
  ~Cyrano() = default;
  void draw(const context& ctx) override;
};
