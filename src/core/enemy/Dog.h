#pragma once
#include "Enemy.h"

class Dog : public Enemy {
 public:
  Dog (Path* beginPath);
  virtual~Dog() = default;
  void draw(const context& ctx) override;
  virtual void serialize(json& glob, json& output)override;
};
