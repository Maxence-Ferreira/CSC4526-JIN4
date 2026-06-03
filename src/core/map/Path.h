#pragma once
#include "Tile.h"

#include <vector>
#include <map>

class Enemy;

class Path : public Tile
{
public:
	Path(int x, int y);
public:
	void addNeighbor(Path* nei);
	Path* next()const;
	virtual void update(int dt);
	virtual void draw(const context & ctx)override;
private:
protected:
	//TODO
	unsigned int cost()const;
	/// <summary>
	/// Dijkstra
	/// </summary>
	void repath();
	std::vector<Path*> m_neighbors;
	std::vector<Enemy*> m_enemies;
	unsigned int m_distance;
	Path* m_next;
};