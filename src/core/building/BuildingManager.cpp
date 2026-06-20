#include "BuildingManager.h"

#include <random>

#include "Archer.h"
#include "Canon.h"
#include "Post.h"

BuildingManager::BuildingManager(Terrain* terter) : m_terrain(terter), post(),
m_building_cast{  }, buildings{},m_placeholder() {
    m_building_cast["Archer"] = std::make_unique<Archer>(100); 
    m_building_cast["Canon"] = std::make_unique<Canon>(200);
}

void BuildingManager::removeDeadBuildings() {
    std::erase_if(buildings, [](std::unique_ptr<Building>& b) {return !b->isAlive(); });
}

void BuildingManager::planConstruct(std::string s)
{
    if (m_placeholder)return;
    m_placeholder = createBuilding(s);
}

void BuildingManager::update(const context& ctx){

    for (const auto& b : buildings){
        b->update(ctx);
    }
    int sz = buildings.size();
    removeDeadBuildings();
    // re update les nearest building des paths
    if (buildings.size() != sz)
    {
        for (Path* p : m_terrain->getPaths())
        {
            p->invalidNearestBuilding();
            for (auto& b : buildings)
                p->addDistanceFrom(b.get());
        }
    }
    if (m_placeholder && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        auto p = sf::Mouse::getPosition();
        p.x += ctx.offsetX;
        p.y += ctx.offsetY;
        p.x /= TILE_SIZE;
        p.y /= TILE_SIZE;
        Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y));
        if (tr)
        {
            addBuilding(std::move(m_placeholder), tr);
            m_placeholder = 0;
        }
    }
}

void BuildingManager::draw(const context& ctx){
    for (const auto& b : buildings){
        b->draw(ctx);
    }
    post->draw(ctx);
    //
    if (!m_placeholder)return;
    auto p = sf::Mouse::getPosition();
    p.x += ctx.offsetX;
    p.y += ctx.offsetY;
    p.x /= TILE_SIZE;
    p.y /= TILE_SIZE;
    Ground* tr = dynamic_cast<Ground*>(m_terrain->getTile(p.x, p.y)); if (tr)
    if (tr)
    {
        m_placeholder->setOnTile(tr);
        m_placeholder->draw(ctx);
        m_placeholder->setOnTile(0);
    }
}

void BuildingManager::addBuilding(std::string s, Ground* ground){
    if (s == "Post") {
        post = std::make_unique<Post>();
        post->setOnTile(ground);
        return;
    }
    auto a = m_building_cast[s]->clone(ground);
    m_terrain->addBuilding(a.get());
    buildings.push_back(std::move(a));
}

void BuildingManager::addBuilding(std::unique_ptr<Building> b, Ground* ground)
{
    b->setOnTile(ground);               //place sur une tile
    m_terrain->addBuilding(b.get());    //initialise les path dist en fonction du terrain
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
    m_terrain = t;
}
