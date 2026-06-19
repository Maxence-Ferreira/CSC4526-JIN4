#pragma once
#include <vector>
#include <map>

#include "Building.h"
#include "../map/Terrain.h"
#include "../Drawable.h"
#include "Post.h"

class BuildingManager : public Drawable{
 private:
	std::vector<std::unique_ptr<Building>> buildings;
	std::map<std::string, std::unique_ptr<Building>> m_building_cast;
	std::unique_ptr<Post> post;
	std::unordered_map<std::string, int> prices;
	Terrain* terter;
 
public:
  BuildingManager(Terrain* terter);
  ~BuildingManager() = default;


  virtual void draw(const context& ctx)override;
  virtual void update(const context& ctx)override;
  void removeDeadBuildings();
  void addBuilding(std::string s, Ground* ground);
  void addBuildingCast(std::string s, std::unique_ptr<Building> cast);
  void setTerrain(Terrain* t);

};