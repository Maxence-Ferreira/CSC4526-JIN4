#pragma once
#include "Enemy.h"

class MeleeSoldier : public Enemy {
 public:
  MeleeSoldier(Path* beginPath);
  ~MeleeSoldier() = default;
  void draw(const context& ctx) override;
};
