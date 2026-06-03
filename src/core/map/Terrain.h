#pragma once

#include "EndTile.h"
#include "Tile.h"
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
private:
protected:

	std::vector<std::unique_ptr<Tile>> m_tiles;
	std::unique_ptr<Tile> m_tiles;
	const int m_width, m_height;
};