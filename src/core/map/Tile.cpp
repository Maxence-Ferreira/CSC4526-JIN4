#include "Tile.h"

Tile::Tile(int x, int y) : m_x(x),m_y(y)
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
