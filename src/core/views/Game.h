#pragma once

#include "building/BuildingManager.h"
#include "enemy/EnemyManager.h"
#include "View.h"

class Game:public View
{
public:
	Game(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, int difficulty,unsigned int seed = 42);

	// Hérité via View
	virtual void reset() override;
	virtual void handle(const std::optional<sf::Event>& ev) override;
	virtual void update()override;
	virtual void draw()override;
private:
	BuildingManager m_building_manager;
	EnemyManager m_enemy_manager;
	Terrain m_terrain;
	sf::Clock m_clock;
	sf::Font m_font;
	sf::Text m_text_displayer;
};