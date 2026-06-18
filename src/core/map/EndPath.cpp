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
	std::cout << "i have "<<m_enemies.size()<<" enemy" << std::endl;
	for (Enemy* e : m_enemies)
	{
		e->kill();
		m_enemies_in++;
	}
	m_enemies = {};
}

int EndPath::howManyEnemiesIn()
{
	return m_enemies_in;
}
