#pragma once

#include "Path.h"

class EndPath :public Path {
public:
	EndPath(int x, int y);
	EndPath(json& inp);
	virtual void update(const context& ctx) override;
	int howManyEnemiesIn();
private:
	virtual void serialize(json& glob, json& output)override;
protected:
	int m_enemies_in;
};