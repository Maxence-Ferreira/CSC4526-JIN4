#pragma once

#include "EndPath.h"
#include "BeginPath.h"
#include "Tile.h"
#include <vector>
#include <memory>

class Terrain
{
public:
	Terrain(int size_x, int size_y);
public:
	Tile* getTile(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	const std::vector<BeginPath*>& getEntry() const;
	void draw(const context& ctx);
	void update(int dt);
	std::vector<Tile*> pathfind(int from_x, int from_y) const;
private:
protected:
	std::vector<std::unique_ptr<Tile>> m_tiles;
	EndPath* m_end;
	std::vector<BeginPath*> m_inputs;
	const int m_width, m_height;
};