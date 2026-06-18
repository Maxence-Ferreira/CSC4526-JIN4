#pragma once

#include "Path.h"

class EndPath :public Path {
public:
	EndPath(int x, int y);
	virtual void update(const context& ctx) override;
	int howManyEnemiesIn();
private:
protected:
	int m_enemies_in;
};