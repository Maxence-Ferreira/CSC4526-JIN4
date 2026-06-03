#pragma once
#include "Enemy.h"

class FirearmSoldier : public Enemy {
 public:
  FirearmSoldier(double x, double y);
  ~FirearmSoldier() = default;
  void attack() override;
};
