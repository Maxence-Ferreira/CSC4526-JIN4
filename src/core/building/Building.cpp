#include "Building.h"

int Building::getX() const
{
	return m_tile->getX();
}

int Building::getY() const
{
	return m_tile->getY();
}

int Building::distanceTo(Tile* nei) const
{
	return abs(nei->getX() - getX()) + abs(nei->getY() - getY());
}
