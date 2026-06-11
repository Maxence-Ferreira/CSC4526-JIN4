#pragma once
#include <vector>
#include <map>

#include "Building.h"
#include "../map/Terrain.h"
#include "../Drawable.h"

class BuildingManager : public Drawable{
 private:
  std::vector<std::unique_ptr<Building>> buildings;
  std::map<std::string, int> prices ;
  Terrain* terter;
 
  public:
  BuildingManager(Terrain* terter) : terter(terter) { prices = {{"Archer", 100},{"Canon", 300}};};
  ~BuildingManager() = default;


  void draw(const context& ctx);
  void updateBuildings(const context& ctx);
  void removeDeadBuildings(Building* targetBuilding);
  void addBuilding(std::string s, Ground* ground);

};