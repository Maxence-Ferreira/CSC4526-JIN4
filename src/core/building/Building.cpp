#include "Building.h"
#include "./map/Path.h"
#include "./enemy/Attack.h"
#include <iostream>

Building::Building(Ground* tile, int pv_max, int damage, int range, int cooldown, int price)
	:m_tile(tile), m_pv_max(pv_max), m_pv(pv_max), m_damage(damage), m_range(range), m_cooldown(cooldown),m_price(price),m_level(0),m_dead(0),m_cur_cooldown(0),m_curr_target(nullptr), attacks{},m_nearest_path(0)
{
	tile->setBuilding(this);
}

int Building::getX() const
{
	return m_tile?m_tile->getX():0;
}

int Building::getY() const
{
	return m_tile? m_tile->getY():0;
}

void Building::takeDamage(int damage)
{
	if ((m_pv -= damage) <= 0)m_dead = true;
}

bool Building::isAlive() const
{
	return !m_dead;
}

int Building::distanceTo(Tile* nei) const
{
	return abs(nei->getX() - getX()) + abs(nei->getY() - getY());
}

Ground* Building::getTile() const 
{
	return m_tile;
}

Attack* Building::attacking(Tile* targetTile) {
  if (m_cur_cooldown <= 0) {
    m_cur_cooldown = m_cooldown;
    attacks.push_back(std::make_unique<Attack>(m_damage, m_range, m_tile->getX(), m_tile->getY(),
                                               targetTile));
    return attacks.back().get();
  }
  return nullptr;
}

void Building::update(const context& ctx) {

  // recharge de l'attaque
  if (m_cur_cooldown > 0) {
    m_cur_cooldown -= ctx.dt;
  }

  // ciblage
  if (m_curr_target==nullptr) {
    int distance = this->distanceTo(m_curr_target);
    if (distance > m_range || !m_curr_target->hasEntity()) {
      m_curr_target = nullptr;
    }
  }

  if (m_curr_target == nullptr) {
    m_curr_target = setTarget();
  }

  // attaque
  if (m_curr_target != nullptr && m_cooldown <= 0) {
    Attack* newAttack = attacking(m_curr_target);
  }
  for (auto it = attacks.begin(); it != attacks.end();) {
    const auto& cur = (*it);
    cur->update(ctx);
    if (!cur->isActive())
      it = attacks.erase(it);
    else
      it++;
  }
}

void Building::drawAttacks(const context& ctx) {
  for (const auto& att : attacks) att->draw(ctx);
}

Tile* Building::setTarget()
{
    return nullptr;
}

/*
Tile* Building::setTarget() {
  Building* nearest = currentPath->getNearestBuilding();
  if (!nearest) return 0;
  if (attackRange >= nearest->distanceTo(currentPath)) {
    return nearest;
  }
  return nullptr;
}
*/

void Building::addDistanceFrom(Path* path){
    if (m_nearest_path && distanceTo(m_nearest_path) <= distanceTo(path))return;
    m_nearest_path = path;
    path->addDistanceFrom(this);
}
Building::~Building() = default;