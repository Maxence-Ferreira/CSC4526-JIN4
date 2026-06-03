#pragma once
#include "Tile.h"

#include <vector>
#include <map>

class Path : public Tile
{
public:
	Path(int x, int y);
public:
	void addNeighbor(Path* nei);
	Path* next()const;
private:
protected:
	//TODO
	unsigned int cost()const;
	void repath();
	std::vector<Path*> m_neighbors;
	unsigned int m_distance;
	Path* m_next;
};