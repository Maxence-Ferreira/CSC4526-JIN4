#include "BuildingManager.h"

#include <iostream>
#include <random>

#include "Archer.h"
#include "Canon.h"
#include "Post.h"

BuildingManager::BuildingManager(Terrain* terter)
    : m_terrain(terter),
      post(),
      m_building_cast{},
      buildings{},
      m_placeholder(),
      m_destroy_mode(false),
      m_pending_refunds(0),
      m_levelup_mode(false) {
  m_building_cast["Archer"] = std::make_unique<Archer>(100);
  m_building_cast["Canon"] = std::make_unique<Canon>(200);
}

void BuildingManager::removeDeadBuildings() {
  int sz = buildings.size();
  std::erase_if(buildings,
                [](std::unique_ptr<Building>& b) { return !b->isAlive(); });
  if (buildings.size() != sz) m_terrain->setBuildings(buildings);
}

void BuildingManager::planConstruct(std::string s) {
  if (m_placeholder) return;
  m_destroy_mode = false;
  m_placeholder = createBuilding(s);
}

void BuildingManager::update(const context& ctx) {
  for (const auto& b : buildings) {
    b->update(ctx);
  }
  removeDeadBuildings();

  if (m_placeholder && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    auto p = sf::Mouse::getPosition(*ctx.window);
    p.x += ctx.offsetX;
    p.y += ctx.offsetY;
    p.x /= TILE_SIZE;
    p.y /= TILE_SIZE;
    Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y));
    if (tr && !tr->hasEntity()) {
      addBuilding(std::move(m_placeholder), tr);
      m_placeholder = 0;
    }
  }

  if (m_destroy_mode && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    auto p = sf::Mouse::getPosition(*ctx.window);
    p.x += ctx.offsetX;
    p.y += ctx.offsetY;
    p.x /= TILE_SIZE;
    p.y /= TILE_SIZE;
    Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y));

    if (tr && tr->hasEntity()) {
      bool destroyedSomething = false;
      // On vérifie si l'entité sur la case est bien une de nos tours
      for (auto& b : buildings) {
        for (Entity* e : tr->getEntity()) {
          if (b.get() == e) {
            m_pending_refunds += b->getPrice() / 2;
            b->kill();
            destroyedSomething = true;
          }
        }
      }
      if (destroyedSomething) {
        m_destroy_mode = false;
      }
    }
  }

  if (m_levelup_mode && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
    auto p = sf::Mouse::getPosition(*ctx.window);
    p.x += ctx.offsetX;
    p.y += ctx.offsetY;
    p.x /= TILE_SIZE;
    p.y /= TILE_SIZE;
    Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y));

    if (tr && tr->hasEntity()) {
      bool levelUpSomething = false;
      for (auto& b : buildings) {
        for (Entity* e : tr->getEntity()) {
          if (b.get() == e) {
            b->levelUp();
            levelUpSomething = true;
          }
        }
      }
      if (levelUpSomething) {
        m_levelup_mode = false;
      }
    }
  }
}

void BuildingManager::draw(const context& ctx) {
  for (const auto& b : buildings) {
    b->draw(ctx);
  }
  post->draw(ctx);

  if (m_levelup_mode) {
    auto p = sf::Mouse::getPosition(*ctx.window);
    p.x += ctx.offsetX;
    p.y += ctx.offsetY;
    p.x /= TILE_SIZE;
    p.y /= TILE_SIZE;
    Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y));

    if (tr && tr->hasEntity()) {
      bool isTower = false;
      for (auto& b : buildings) {
        for (Entity* e : tr->getEntity()) {
          if (b.get() == e) isTower = true;
        }
      }
      if (isTower) {
        ctx.rm->draw({{p.x * (float)TILE_SIZE, p.y * (float)TILE_SIZE},
                      {(float)TILE_SIZE, (float)TILE_SIZE}},
                     "white", sf::Color(255, 255, 0, 127));
      }
    }
  }

  if (m_destroy_mode) {
    auto p = sf::Mouse::getPosition(*ctx.window);
    p.x += ctx.offsetX;
    p.y += ctx.offsetY;
    p.x /= TILE_SIZE;
    p.y /= TILE_SIZE;
    Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y));

    if (tr && tr->hasEntity()) {
      bool isTower = false;
      for (auto& b : buildings) {
        for (Entity* e : tr->getEntity()) {
          if (b.get() == e) isTower = true;
        }
      }
      if (isTower) {
        ctx.rm->draw({{p.x * (float)TILE_SIZE, p.y * (float)TILE_SIZE},
                      {(float)TILE_SIZE, (float)TILE_SIZE}},
                     "white", sf::Color(255, 0, 0, 127));
      }
    }
  }

  //
  if (!m_placeholder) return;
  auto p = sf::Mouse::getPosition(*ctx.window);
  p.x += ctx.offsetX;
  p.y += ctx.offsetY;
  p.x /= TILE_SIZE;
  p.y /= TILE_SIZE;
  Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y));
  if (tr)
    if (tr && !tr->hasEntity()) {
      ctx.rm->draw({{(p.x - m_placeholder->getRange()) * TILE_SIZE,
                     (p.y - m_placeholder->getRange()) * TILE_SIZE},
                    {(m_placeholder->getRange() * 2 + 1) * TILE_SIZE,
                     (m_placeholder->getRange() * 2 + 1) * TILE_SIZE}},
                   "white", sf::Color(255, 0, 0, 127));
      m_placeholder->setOnTile(tr);
      m_placeholder->draw(ctx);
      m_placeholder->setOnTile(0);
    }
}

void BuildingManager::addBuilding(std::string s, Ground* ground) {
  if (s == "Post") {
    post = std::make_unique<Post>();
    post->setOnTile(ground);
    return;
  }
  auto a = m_building_cast[s]->clone(ground);
  a->setOnTile(ground);
  m_terrain->addBuilding(a.get());
  buildings.push_back(std::move(a));
}

void BuildingManager::addBuilding(std::unique_ptr<Building> b, Ground* ground) {
  b->setOnTile(ground);  // place sur une tile
  m_terrain->addBuilding(
      b.get());  // initialise les path dist en fonction du terrain
  buildings.push_back(std::move(b));
}

std::unique_ptr<Building> BuildingManager::createBuilding(std::string s) {
  return m_building_cast[s]->clone();
}

void BuildingManager::addBuildingCast(std::string s,
                                      std::unique_ptr<Building> cast) {
  m_building_cast[s] = std::move(cast);
}

void BuildingManager::setTerrain(Terrain* t) { m_terrain = t; }

int BuildingManager::getPrice(const std::string& buildingName) const {
  auto it = m_building_cast.find(buildingName);
  if (it != m_building_cast.end()) {
    return it->second->getPrice();
  }
  return INT32_MAX;
}

int BuildingManager::getPrice(const Building* b) const { return b->getPrice(); }

void BuildingManager::planDestruct() {
  m_placeholder = nullptr;
  m_destroy_mode = true;
}

int BuildingManager::collectRefunds() {
  int refunds = m_pending_refunds;
  m_pending_refunds = 0;
  return refunds;
}

void BuildingManager::levelUpBuilding() {
  m_placeholder = nullptr;
  m_levelup_mode = true;
}

