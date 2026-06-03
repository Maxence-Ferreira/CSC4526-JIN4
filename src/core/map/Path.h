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
private:
protected:
	std::vector<Path*> m_neighbors;
};