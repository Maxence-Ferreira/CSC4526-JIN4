#include "Terrain.h"

#include "Path.h"
#include "EndPath.h"
#include "BeginPath.h"
#include "Ground.h"

Terrain::Terrain(int size_x, int size_y) : m_tiles((long long)size_x* (long long)size_y),m_width(size_x),m_height(size_y)
{
	std::vector<Path*> paths;
	for (int j = 0; j < size_y; j++)
		for (int i = 0; i < size_x; i++)
			m_tiles[j* (long long)size_x+i]=std::make_unique<Ground>(i,j);
}

int Terrain::getWidth() const
{
	return m_width;
}

int Terrain::getHeight() const
{
	return m_height;
}

Tile* Terrain::getTile(int x, int y) const
{
	return m_tiles[y * (long long)m_width + x].get();
}
