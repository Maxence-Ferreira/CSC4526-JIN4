#pragma once

#include "Tile.h"
#include <vector>
#include <memory>

class Terrain
{
public:
	Terrain(int size_x, int size_y);
private:
protected:
	std::vector<std::unique_ptr<Tile>> m_tiles;
};