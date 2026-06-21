#include "EndPath.h"
#include <iostream>

EndPath::EndPath(int x, int y):Path(x,y),m_enemies_in(0)
{
}

void EndPath::update(const context& ctx)
{
	repath();
	//Path::update(ctx);
	if (m_enemies.empty())return;
	for (Enemy* e : m_enemies)
	{
		e->reachObjective();
		m_enemies_in++;
	}
	m_enemies = {};
}

int EndPath::howManyEnemiesIn()
{
	return m_enemies_in;
}
