#include "Terrain.h"

#include "Path.h"
#include "EndPath.h"
#include "BeginPath.h"
#include "Ground.h"

#include <map>

Terrain::Terrain(int size_x, int size_y) : m_tiles((long long)size_x* (long long)size_y),m_width(size_x),m_height(size_y),m_end(0),m_inputs{}
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

const std::vector<BeginPath*>& Terrain::getEntry() const
{
	return m_inputs;
}

void Terrain::draw(const context& ctx)
{
	for (const auto& i : m_tiles)
	{
		i->draw(ctx);
	}
}

void Terrain::update(int dt)
{
	if(m_end)m_end->update(dt);
}

std::vector<Tile*> Terrain::pathfind(int from_x, int from_y) const
{
	Path* p=dynamic_cast<Path*>(m_tiles[from_y * (long long)m_width + from_x].get());
	if(!p)
		return std::vector<Tile*>();
	std::vector<Tile*>r{ p };
	while (p->next()) {
		p = p->next();
		r.push_back(p);
	}
	return r;
}

Tile* Terrain::getTile(int x, int y) const
{
	return m_tiles[y * (long long)m_width + x].get();
}
