#pragma once
#include "Entity.h"
#include "./map/Ground.h"
#include "./map/Path.h"
#include "./enemy/Attack.h"
#include "./enemy/Enemy.h"

class Ground;
class Enemy;
class Attack;
class Path;

class Building : public Entity{
public:
	Building(
		Ground* tile,
		int pv_max,
		int damage,
		int range,
		int cooldown,
		int price);
	int getX() const;
	int getY() const;
	void takeDamage(int damage) override;
	bool isAlive() const override;
	int distanceTo(Tile*) const;
	virtual~Building();
	Ground* getTile() const;
	virtual Attack* attacking(Tile* targetTile);
	virtual void update(const context& ctx) override;
  	void drawAttacks(const context& ctx);
 	Tile* setTarget();
	void addDistanceFrom(Path* path);
protected:
private:
	Ground* m_tile;
	Tile* m_curr_target;
	int m_pv_max;
	int m_pv;
	int m_damage;
	int m_range;
	int m_cooldown;
	bool m_dead;
	int m_cur_cooldown = 0;
	int m_level;
	int m_price;
	Path* m_nearest_path;
	std::vector<std::unique_ptr<Attack>> attacks;
};