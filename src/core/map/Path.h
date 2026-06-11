#pragma once
#include "Tile.h"
#include "building/Building.h"
#include <vector>
#include <map>

class Enemy;
class Building;

class Path : public Tile
{
public:
	Path(int x, int y);
public:
	void addNeighbor(Path* nei);
	void addDistanceFrom(Building* nei);
	Building* getNearestBuilding();
	Path* next()const;
	void addEnemy(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	virtual void update(const context& ctx)override;
	virtual void draw(const context & ctx)override;
	virtual std::vector<Entity*> getEntity()const override;
private:
	static std::unique_ptr<sf::RectangleShape> createSprite();
	sf::Angle angle;
	static std::unique_ptr<sf::RectangleShape> g_sprite;
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
	Building* m_nearest_building;
};