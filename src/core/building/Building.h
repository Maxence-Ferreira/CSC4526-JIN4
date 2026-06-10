#pragma once
#include "Drawable.h"
#include "./map/Ground.h"
#include "./enemy/Enemy.h"

class Ground;
class Enemy;

class Building : public Drawable{
public:
	Building(
		Ground* tile,
		int pv_max,
		int dammage,
		int range,
		int cooldown,
		int price);
	int getX() const;
	int getY() const;
	void takeDamage(int damage);
	bool isAlive() const;
	int distanceTo(Tile*) const;
	virtual~Building() = default;
protected:
private:
	Ground* m_tile;
	Enemy* m_target;
	int m_pv_max;
	int m_pv;
	int m_dammage;
	int m_range;
	int m_cooldown;
	bool m_dead;
	int m_cur_cooldown;
	int m_level;
	int m_price;
};