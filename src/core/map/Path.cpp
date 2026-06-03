#include "Path.h"
#include <algorithm>

Path::Path(int x, int y):Tile(x,y), m_neighbors{}
{
}

void Path::addNeighbor(Path* nei)
{
	if (!nei||std::find(m_neighbors.begin(), m_neighbors.end(),nei)!= m_neighbors.end())return;
	if ((nei->m_x-m_x)^^(nei->m_y-m_y))
	m_neighbors.push_back(nei);
	nei->m_neighbors.push_back(this);
}
