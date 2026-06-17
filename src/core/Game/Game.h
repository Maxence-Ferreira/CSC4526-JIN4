#pragma once

#include "common.h"
#include "building/BuildingManager.h"
#include "enemy/EnemyManager.h"
#include "common.h"

class Game
{
public:
	Game(sf::RenderWindow* rw, std::string tileset, int difficulty,unsigned int seed = 42);
	void setTileNames(const std::vector<std::string>& names);
	void update();
	void draw();
private:
	context m_context;
	BuildingManager m_building_manager;
	EnemyManager m_enemy_manager;
	Terrain m_terrain;
	sf::Clock m_clock;
	sf::Font m_font;
	sf::Text m_text_displayer;
};