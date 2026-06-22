#pragma once
#include <vector>
#include <map>

#include "Building.h"
#include "../map/Terrain.h"
#include "../Drawable.h"
#include "Post.h"
#include "Serializable.h"
#include <SFML/Graphics.hpp>

class BuildingManager : public Drawable, public Serializable {
 private:
	std::vector<std::unique_ptr<Building>> buildings;
	std::map<std::string, std::unique_ptr<Building>> m_building_cast;
	std::unique_ptr<Post> post;
	Terrain* m_terrain;
	std::unique_ptr<Building> m_placeholder;
  bool m_destroy_mode ;
  int m_pending_refunds ;
  bool m_levelup_mode;
  sf::Font m_font;
  sf::Text m_price_text;
  int m_pending_costs ;
  int m_available_money ;
 
public:
	BuildingManager(Terrain* terter);
	BuildingManager(Terrain* terter, json& glob, json& save);
  ~BuildingManager() = default;


  virtual void draw(const context& ctx)override;
  virtual void update(const context& ctx)override;
  virtual void serialize(json& glob, json& output)override;
  void removeDeadBuildings();
  void planConstruct(std::string s);
  void addBuilding(std::string s, Ground* ground);
  void addBuilding(std::unique_ptr<Building> b, Ground* ground);
  std::unique_ptr<Building> createBuilding(std::string s);
  void addBuildingCast(std::string s, std::unique_ptr<Building> cast);
  void setTerrain(Terrain* t);
  int getPrice(const std::string& buildingName) const;
  int getPrice(const Building* b) const;
  void planDestruct();
  int collectRefunds();
  void levelUpBuilding();
  void setAvailableMoney(int money);
  int collectCosts();
  void drawUI(const context& ctx);
};