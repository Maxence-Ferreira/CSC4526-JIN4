#pragma once
#include "Enemy.h"

class Kamikaze : public Enemy {
 private:
  bool isExploding = false;
  float explosionTimer = 2000.0f;
 public:
	Kamikaze(Path* beginPath);
	Kamikaze(json& save, Path* p);
	~Kamikaze() = default;
	virtual Attack* attacking(Building* targetBuilding) override;
	void draw(const context& ctx) override;
	virtual void update(const context& ctx) override;
	virtual void serialize(json& glob, json& output)override;
};
