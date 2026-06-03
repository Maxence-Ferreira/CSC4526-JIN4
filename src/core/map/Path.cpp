#include "Path.h"
#include <algorithm>

Path::Path(int x, int y):Tile(x,y), m_neighbors{}
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
