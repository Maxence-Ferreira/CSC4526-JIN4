#include "Tile.h"

Tile::Tile(int x, int y) : m_x(x),m_y(y)
{

}

Tile::Tile(json& inp):m_x(inp["x"]), m_y(inp["y"])
{
}

int Tile::getX() const
{
	return m_x;
}

int Tile::getY() const
{
	return m_y;
}

void Tile::serialize(json& glob, json& output)
{
	output["x"] = m_x;
	output["y"] = m_y;
}

