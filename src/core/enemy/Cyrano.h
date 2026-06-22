#pragma once
#include "Enemy.h"

class Cyrano : public Enemy {
 public:
	Cyrano(Path* beginPath);
	Cyrano(json& save, Path* current);
	virtual~Cyrano() = default;
	void draw(const context& ctx) override;
	virtual void serialize(json& glob, json& output)override;
};
