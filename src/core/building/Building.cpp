#include "Building.h"
#include "./map/Path.h"
#include "./enemy/Attack.h"
#include <iostream>
#include <queue>
#include <unordered_set>

Building::Building(Ground* tile, int pv_max, int damage, int range, int cooldown, int price)
	:m_tile(tile), m_pv_max(pv_max), m_pv(pv_max), m_damage(damage), m_range(range), m_cooldown(cooldown),m_price(price),m_level(0),m_dead(0),m_cur_cooldown(0),m_curr_target(nullptr), attacks{},m_tracked_path(),m_path_at_range(), m_nearest_path(0)
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
                                               targetTile, "blue"));
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
  if (m_curr_target!=nullptr) {
    int distance = this->distanceTo(m_curr_target);
    if (distance > m_range || !m_curr_target->hasEntity()) {
      m_curr_target = nullptr;
    }
  }

  if (m_curr_target == nullptr) {
    m_curr_target = setTarget();
  }

  // attaque
  if (m_curr_target != nullptr && m_cur_cooldown <= 0) {
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

//récuperer aléatoirement un path
Tile* Building::setTarget() {
  if (!m_nearest_path) return 0;
  if (m_range >= this->distanceTo(m_nearest_path)&&m_nearest_path->hasEntity()) {
    return m_nearest_path;
  }
  return nullptr;
}


void Building::addDistanceFrom(Path* path){
    if (m_nearest_path && distanceTo(m_nearest_path) <= distanceTo(path))return;
    m_nearest_path = path;
    path->addDistanceFrom(this);
    /*
    std::queue<Path*> totreat;
    std::unordered_set<Path*> treated;
    totreat.push(m_nearest_path);
    Path* cur;
    int dist;
    while (!totreat.empty())
    {
        cur = totreat.front();
        totreat.pop();
        if (treated.contains(cur))continue;
        dist = std::max(std::abs(cur->getX() - m_tile->getX()), std::abs(cur->getY() - m_tile->getY()));
        treated.insert(cur);
        m_path_at_range[dist].push_back(cur);
        for (Path* p : cur->getNeighbors())
        {
            if (!treated.contains(p))
            {
                totreat.push(p);
            }
        }
    }
    */
    m_path_at_range[std::max(std::abs(path->getX() - m_tile->getX()), std::abs(path->getY() - m_tile->getY()))].push_back(path);
    changeRange(m_range);
}
void Building::changeRange(int range)
{
    m_range = range;
    m_tracked_path = {};
    for (int i = 1; i <= range; i++)
    {
        m_tracked_path.insert(m_tracked_path.end(),m_path_at_range[i].begin(), m_path_at_range[i].end());
    }
}
Building::~Building() = default;