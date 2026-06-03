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
	for (auto it = paths.begin(); it != paths.end(); it++)
		for (auto it2 = it+1; it2 != paths.end(); it2++)
			(*it)->addNeighbor(*it2);//auto eject non neighbor case 
}

int Terrain::getWidth() const
{
	return m_width;
}

int Terrain::getHeight() const
{
	return m_height;
}

void Terrain::update(int dt)
{
	//
}

std::vector<Tile*> Terrain::pathfind(int from_x, int from_y) const
{
	return std::vector<Tile*>();
}

Tile* Terrain::getTile(int x, int y) const
{
	return m_tiles[y * (long long)m_width + x].get();
}
