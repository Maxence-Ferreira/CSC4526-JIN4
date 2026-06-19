#include "BuildingManager.h"

#include <random>

#include "Archer.h"
#include "Canon.h"
#include "Post.h"

BuildingManager::BuildingManager(Terrain* terter) : terter(terter), post(),
m_building_cast{  }, buildings{} {
    m_building_cast["Archer"] = std::make_unique<Archer>(100); 
    m_building_cast["Canon"] = std::make_unique<Canon>(200);
}

void BuildingManager::removeDeadBuildings() {
    std::erase_if(buildings, [](std::unique_ptr<Building>& b) {return !b->isAlive(); });
}

void BuildingManager::update(const context& ctx){

    for (const auto& b : buildings){
        b->update(ctx);
    }
    int sz = buildings.size();
    removeDeadBuildings();
    if (buildings.size() != sz)
    {
        for (Path* p : terter->getPaths())
        {
            p->invalidNearestBuilding();
            for (auto& b : buildings)
                p->addDistanceFrom(b.get());
        }
    }
}

void BuildingManager::draw(const context& ctx){
  for (const auto& b : buildings){
    b->draw(ctx);
  }
  post->draw(ctx);
}

void BuildingManager::addBuilding(std::string s, Ground* ground){
    if (s == "Post") {
        post = std::make_unique<Post>();
        post->setOnTile(ground);
        return;
    }
    auto a = m_building_cast[s]->clone(ground);
    terter->addBuilding(a.get());
    buildings.push_back(std::move(a));
}

void BuildingManager::addBuilding(std::unique_ptr<Building> b, Ground* ground)
{
    terter->addBuilding(b.get());
    buildings.push_back(std::move(b));
}

std::unique_ptr<Building> BuildingManager::createBuilding(std::string s)
{
    return m_building_cast[s]->clone();
}

void BuildingManager::addBuildingCast(std::string s, std::unique_ptr<Building> cast)
{
    m_building_cast[s] = std::move(cast);
}

void BuildingManager::setTerrain(Terrain* t)
{
    terter = t;
}
