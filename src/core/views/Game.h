#pragma once

#include "building/BuildingManager.h"
#include "enemy/EnemyManager.h"
#include "View.h"
#include "SFML/Audio.hpp"

class Game:public View
{
public:
	Game(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, int difficulty,unsigned int seed = 42);

	// H�rit� via View
	virtual void reset() override;
	virtual void handle(const std::optional<sf::Event>& ev) override;
	virtual void update()override;
	virtual void draw()override;
	virtual void onEnter()override;
	virtual void onExit()override;
private:
	virtual bool behavior(const std::string& action_name) override;
private:
	int m_difficulty;
	std::unique_ptr<Terrain> m_terrain;
	std::unique_ptr<BuildingManager> m_building_manager;
	std::unique_ptr<EnemyManager> m_enemy_manager;
	sf::Clock m_clock;
	sf::Font m_font;
	sf::Text m_text_displayer;
	sf::Text m_money_displayer;
	sf::Music m_song;
	int m_money;
};