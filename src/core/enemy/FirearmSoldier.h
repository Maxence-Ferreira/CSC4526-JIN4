#pragma once
#include "Enemy.h"

class FirearmSoldier : public Enemy {
 public:
	FirearmSoldier(Path* beginPath);
	FirearmSoldier(json& save,Path* current);
	virtual ~FirearmSoldier() = default;
	void draw(const context& ctx) override;
	virtual void serialize(json& glob, json& output)override;
};
