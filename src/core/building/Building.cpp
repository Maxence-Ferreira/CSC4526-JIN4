#include "Building.h"

Building::Building(Ground* tile, int pv_max, int dammage, int range, int cooldown, int price)
	:m_tile(tile), m_pv_max(pv_max), m_pv(pv_max), m_dammage(dammage), m_range(range), m_cooldown(cooldown),m_price(price),m_level(0),m_dead(0),m_cur_cooldown(0),m_target(0)
{
}

int Building::getX() const
{
	return m_tile->getX();
}

int Building::getY() const
{
	return m_tile->getY();
}

bool Building::isAlive() const
{
	return !m_dead;
}

int Building::distanceTo(Tile* nei) const
{
	return abs(nei->getX() - getX()) + abs(nei->getY() - getY());
}
