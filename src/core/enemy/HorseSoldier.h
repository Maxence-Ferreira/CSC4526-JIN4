#pragma once
#include "Enemy.h"

class HorseSoldier : public Enemy {
 public:
	 HorseSoldier(Path* beginPath);
	 HorseSoldier(json& save , Path* current);
  ~HorseSoldier() = default;
  void draw(const context& ctx) override;
  virtual void serialize(json& glob, json& output)override;
};
