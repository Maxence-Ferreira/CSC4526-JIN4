#pragma once

#include <vector>
#include "Tile.h"
#include <memory>

class Terrain
{
public:
private:
protected:
	std::vector<std::unique_ptr<Tile>> m_tiles;
};