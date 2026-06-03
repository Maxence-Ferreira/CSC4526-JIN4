#include "Terrain.h"

Terrain::Terrain(int size_x, int size_y) : m_tiles((long long)size_x* (long long)size_y),m_width(size_x),m_height(size_y)
{
	for (int j = 0; j < size_y; j++)
		for (int i = 0; i < size_x; i++)
			m_tiles[j* (long long)size_x+i]=std::make_unique<Tile>(i,j);
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
