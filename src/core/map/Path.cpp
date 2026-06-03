#include "Path.h"
#include <algorithm>
#include <queue>
#include <unordered_set>
#include "enemy/Enemy.h"

Path::Path(int x, int y):Tile(x,y), m_neighbors{},m_distance{(unsigned int)(-1)},m_next(0),m_enemies{}
{
}

void Path::addNeighbor(Path* nei)
{
	if (!nei||std::find(m_neighbors.begin(), m_neighbors.end(),nei)!= m_neighbors.end())return;
	int dx = nei->m_x - m_x;
	int dy = nei->m_y - m_y;
	if (dx * dx + dy * dy != 1)return;
	m_neighbors.push_back(nei);
	nei->m_neighbors.push_back(this);
}

Path* Path::next() const
{
	return m_next;
}

void Path::update(int dt)
{
	for (Enemy* e : m_enemies)
	{
		e->move(dt);
	}
}

void Path::draw(const context& ctx)
{
}

unsigned int Path::cost() const
{
	return 1;
}

void Path::repath()
{
	//liste trié
	std::priority_queue<std::pair<unsigned int,Path*>,std::vector<std::pair<unsigned int, Path*>>,std::greater<>>totreat;
	totreat.push({ 0,this });
	m_distance = 0;
	while (!totreat.empty()) {
		// On prend le plus petit
		auto[dist,cur]= totreat.top();
		totreat.pop();
		if (dist > cur->m_distance)continue;
		//on update ses neighbors si ca diminue leur distance
		for (Path* p : cur->m_neighbors)
		{
			unsigned int d = dist + p->cost();
			if (d < p->m_distance)
			{
				p->m_distance = d;
				p->m_next = cur;
				totreat.push({ d,p });
			}
		}
	}
}
