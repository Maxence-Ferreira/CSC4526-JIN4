#pragma once
#include "Enemy.h"

class Cyrano : public Enemy {
 public:
  Cyrano(double x, double y);
  ~Cyrano() = default;
  void attack() override;
};
