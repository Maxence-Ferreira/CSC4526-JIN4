#pragma once

#include "EndPath.h"
#include "BeginPath.h"
#include "Tile.h"
#include <vector>
#include <memory>
#include <random>
#include "building/Building.h"

class Terrain :public Drawable
{
public:
	Terrain(int size_x, int size_y, int difficulty, std::mt19937& rand);
public:
	Tile* getTile(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	int countEnemyInPost() const;
	void setBuildings(const std::vector<std::unique_ptr<Building>>& buildings);
	const std::vector<BeginPath*>& getEntry() const;
	void draw(const context& ctx)override;
	virtual void update(const context& ctx)override;
	std::vector<Tile*> pathfind(int from_x, int from_y) const;
	void addBuilding(Building*ptr) const;
	std::vector<Path*> getPaths() {return m_paths;};
private:
#ifdef TESTING
public:
#else
protected:
#endif
	std::vector<std::unique_ptr<Tile>> m_tiles;
	EndPath* m_end;
	std::vector<BeginPath*> m_inputs;
	std::vector<Path*> m_paths;
	const int m_width, m_height;
};