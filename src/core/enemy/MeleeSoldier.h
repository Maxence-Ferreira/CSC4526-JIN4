#pragma once
#include "Enemy.h"

class MeleeSoldier : public Enemy {
 public:
  MeleeSoldier(double x, double y);
  ~MeleeSoldier() = default;
  void attacking() override;
};
