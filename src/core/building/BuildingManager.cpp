#include "BuildingManager.h"

#include <random>

#include "Archer.h"
#include "Canon.h"
#include "Post.h"


void BuildingManager::removeDeadBuildings(Building* targetBuilding) {
    if (targetBuilding->isAlive()) {
        return;
    }
    
    for (auto it = buildings.begin(); it != buildings.end(); ++it) {
        if (it->get() == targetBuilding) {
            buildings.erase(it);
            return;
        }
    }
}

void BuildingManager::updateBuildings(const context& ctx){
  for (const auto& b : buildings){
    b->update(ctx);
  }
}

void BuildingManager::draw(const context& ctx){
  for (const auto& b : buildings){
    b->draw(ctx);
  }
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
        auto p = std::make_unique<Post>(ground, 3);
        buildings.push_back(std::move(p));
    }
}