#include "Path.h"
#include <algorithm>
#include <queue>

Path::Path(int x, int y):Tile(x,y), m_neighbors{},m_distance{-1},m_next(0)
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

unsigned int Path::cost() const
{
	return 1;
}

void Path::repath()
{
	std::priority_queue<
		std::pair<unsigned int, Path*>,
		std::vector<std::pair<unsigned int, Path*>>, 
		std::greater<>> 
		distmap;
	Path* cur = this;
	Path* c;
	unsigned int d = 0;
	while (true) {
		for (Path* p : cur->m_neighbors)
		{
			if (p->cost() + cur->m_distance < p->m_distance)
			{
				p->m_distance = p->cost() + cur->m_distance;
				distmap.push({ p->m_distance,p });
			}
		}
		while (!distmap.empty())
		{
			const auto& [d_, c_] = distmap.top();
			d = d_;
			c = c_;
			distmap.pop();

			if (d == c->m_distance)
				break;
		}
		if (distmap.empty() && d != c->m_distance)
			break;
		c->m_next = cur;
		cur = c;
	}
}
