#include "Building.h"

#include <iostream>
#include <queue>
#include <unordered_set>

#include "./enemy/Attack.h"
#include "./map/Path.h"

Building::Building(int pv_max, int damage, int range,
    int cooldown, int price)
    : m_tile(0),
    m_pv_max(pv_max),
    m_pv(pv_max),
    m_damage(damage),
    m_range(range),
    m_cooldown(cooldown),
    m_price(price),
    m_level(0),
    m_dead(0),
    m_cur_cooldown(0),
    m_curr_target(nullptr),
    attacks{},
    m_tracked_path(),
    m_path_at_range(),
    m_nearest_path(0) {
}
Building::Building(const Building& b)
    : m_tile(),
    m_pv_max(b.m_pv_max),
    m_pv(b.m_pv_max),
    m_damage(b.m_damage),
    m_range(b.m_range),
    m_cooldown(b.m_cooldown),
    m_price(b.m_price),
    m_level(0),
    m_dead(0),
    m_cur_cooldown(0),
    m_curr_target(nullptr),
    attacks{},
    m_tracked_path(),
    m_path_at_range(),
    m_nearest_path() {
}

int Building::getX() const { return m_tile ? m_tile->getX() : 0; }

int Building::getY() const { return m_tile ? m_tile->getY() : 0; }

void Building::takeDamage(int damage) {
  if ((m_pv -= damage) <= 0) m_dead = true;
}

bool Building::isAlive() const { return !m_dead; }

int Building::distanceTo(Tile* nei) const {
  return abs(nei->getX() - getX()) + abs(nei->getY() - getY());
}

Ground* Building::getTile() const { return m_tile; }

void Building::setOnTile(Ground* tile)
{
    m_tile = tile;
    m_tile->setBuilding(this);
}

Attack* Building::attacking(Tile* targetTile) {
  if (m_cur_cooldown <= 0) {
    m_cur_cooldown = m_cooldown;
    attacks.push_back(std::make_unique<Attack>(
        m_damage, m_range, m_tile->getX() + .5f, m_tile->getY() + .5f,
        targetTile, projectileSkin()));
    return attacks.back().get();
  }
  return nullptr;
}

std::string Building::projectileSkin() const
{
    return "";
}

void Building::update(const context& ctx) {
  // recharge de l'attaque
  if (m_cur_cooldown > 0) {
    m_cur_cooldown -= ctx.dt;
  }

  // ciblage
  if (m_curr_target != nullptr) {
    int distance = this->distanceTo(m_curr_target);
    if (distance > m_range || !m_curr_target->hasEntity()) {
      m_curr_target = nullptr;
    }
  }

  if (m_curr_target == nullptr) {
    m_curr_target = setTarget(*ctx.rand);
  }

  // attaque
  if (m_curr_target != nullptr && m_cur_cooldown <= 0) {
    Attack* newAttack = attacking(m_curr_target);
    m_curr_target = nullptr;
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

// r�cuperer al�atoirement un path
Tile* Building::setTarget(std::mt19937& rand) {
  /*
if (!m_nearest_path) return 0;
if (m_range >= this->distanceTo(m_nearest_path)&&m_nearest_path->hasEntity()) {
  return m_nearest_path;
}
*/
  return nullptr;
}

void Building::addDistanceFrom(Path* path) {
  if (m_nearest_path == path) return;
  m_path_at_range[std::max(std::abs(path->getX() - m_tile->getX()),
                           std::abs(path->getY() - m_tile->getY()))]
      .push_back(path);
  changeRange(m_range);
  if (m_nearest_path && distanceTo(m_nearest_path) <= distanceTo(path)) return;
  m_nearest_path = path;
}
void Building::changeRange(int range) {
  m_range = range;
  m_tracked_path = {};
  for (int i = 1; i <= range; i++) {
    m_tracked_path.insert(m_path_at_range[i].begin(), m_path_at_range[i].end());
  }
}

void Building::levelUp() {
  if (m_level < 5) {
    m_level += 1;
    m_pv_max *= 1.5;
    m_pv = m_pv_max;
    m_damage *= 1.2;
    if (m_level % 2 == m_level / 2) {
      changeRange(m_range + 1);
    }
  }
  else {return;}
}

Building::~Building() = default;

int Building::getRange() { return m_range; };
int Building::getPrice() { return m_price; };