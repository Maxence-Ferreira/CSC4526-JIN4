#pragma once

#include "Path.h"

class EndPath :public Path {
public:
	EndPath(int x, int y);
	virtual void update(const context& ctx) override;
	int howManyEnemiesIn();
private:
	virtual void serialize(json& output)override;
protected:
	int m_enemies_in;
};