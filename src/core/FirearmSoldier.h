#pragma once
#include "Enemy.h"

class FirearmSoldier : public Enemy {
 private:
  double currentCooldown;  // temps restant avant de pouvoir attaquer à nouveau

 public:
  FirearmSoldier(double x, double y);
  ~FirearmSoldier() = default;
  void attack() override;
};
