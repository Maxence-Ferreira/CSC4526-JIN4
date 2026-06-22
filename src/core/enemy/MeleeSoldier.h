#pragma once
#include "Enemy.h"

class MeleeSoldier : public Enemy {
 public:
	MeleeSoldier(Path* beginPath);
	MeleeSoldier(json& save, Path* current);
	~MeleeSoldier() = default;
	void draw(const context& ctx) override;
	virtual void serialize(json& glob, json& output)override;
};
