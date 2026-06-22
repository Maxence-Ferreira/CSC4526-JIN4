#pragma once
#include "Enemy.h"

class Cyrano : public Enemy {
 public:
  Cyrano(Path* beginPath);
  virtual~Cyrano() = default;
  void draw(const context& ctx) override;
  virtual void serialize(json& glob, json& output)override;
};
