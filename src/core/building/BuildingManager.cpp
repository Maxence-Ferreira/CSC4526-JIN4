#include "BuildingManager.h"

#include <random>

#include "Archer.h"
#include "Canon.h"
#include "Post.h"

BuildingManager::BuildingManager(Terrain* terter) : terter(terter),post(), prices{ {"Archer", 100},{"Canon", 300} } {
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
    if(s=="Archer"){
        auto a=std::make_unique<Archer>(ground, prices["Archer"]);
        terter->addBuilding(a.get());
        buildings.push_back(std::move(a));
        prices["Archer"]*=1.2;
    }
    if (s == "Canon") {
        auto c = std::make_unique<Canon>(ground, prices["Canon"]);
        terter->addBuilding(c.get());
        buildings.push_back(std::move(c));
        prices["Canon"] *= 1.2;
    }
    if (s == "Post") {
        post = std::make_unique<Post>(ground, 3);
    }
}