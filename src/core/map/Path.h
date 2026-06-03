#pragma once
#include "Tile.h"

#include <vector>

class Path : public Tile
{
public:
	Path(int x, int y);
public:
	void addNeighbor(Path* nei);
	int cost()const;
	Path* next()const;
private:
protected:
	std::vector<Path*> m_neighbors;
	unsigned int m_distance;
	std::vector<Path*> m_way;
};