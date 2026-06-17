#include "EndPath.h"
#include <iostream>

EndPath::EndPath(int x, int y):Path(x,y)
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
	}
	m_enemies = {};
}
