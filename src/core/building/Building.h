#pragma once
#include "Entity.h"
#include "./map/Ground.h"
#include "./map/Path.h"
#include "./enemy/Attack.h"
#include "./enemy/Enemy.h"
#include <map>
#include <unordered_set>

class Ground;
class Enemy;
class Attack;
class Path;

class Building : public Entity{
public:
	Building(
		int pv_max,
		int damage,
		int range,
		int cooldown,
		int price);
	Building(
		const Building & b);
	virtual~Building()override;
	int getX() const;
	int getY() const;
	void takeDamage(int damage) override;
	bool isAlive() const override;
	int distanceTo(Tile*) const;
	Ground* getTile() const;
	void setOnTile(Ground* tile);
	virtual Attack* attacking(Tile* targetTile);
	virtual void update(const context& ctx) override;
  	void drawAttacks(const context& ctx);
	void addDistanceFrom(Path* path);
	void changeRange(int range);
	void levelUp();
	virtual std::unique_ptr<Building> clone(Ground* ground) = 0;
	int getRange();
	int getPrice();

private:
protected:
	virtual Tile* setTarget(std::mt19937& rand);
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
	std::unordered_set<Path*> m_tracked_path;
	std::map<int,std::vector<Path*>> m_path_at_range;
	std::vector<std::unique_ptr<Attack>> attacks;
};