#include "myMain.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "map/Terrain.h"
#include "common.h"
#include "enemy/Cyrano.h"
#include "building/Archer.h"
#include "enemy/EnemyManager.h"
#include "building/BuildingManager.h"
#include "Graphics/ResourceManager.h"

using namespace std;

int myMain() {
	const char* names[] = {
		"post",
		"archer",
		"canon",
		"ground1",
		"ground2",
		"ground3",
		"ground4",
		"path1",
		"path2",
		"path3",
		"path4",
		"cyrano1",
		"cyrano2",
		"dog1",
		"dog2",
		"firearm1",
		"firearm2",
		"horse1",
		"horse2",
		"kamikaze1",
		"kamikaze2",
		"melee1",
		"melee2",
		"cannonball",
		"arrow"};
	cout << "HW" << endl;
	sf::RenderWindow win(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)),"Post Me If You Can");
	sf::Font f("resources/Cyrano.ttf");
	sf::Text t(f);
	context c = {
		.time = 0,
		.dt = 0,
		.offsetX = 0,
		.offsetY = 0,
		.window = &win,
		.rm = std::make_unique<ResourceManager>("resources/tileset.png"),
		.rand=std::mt19937(std::random_device()()),
	};
	for (int i = 0; i < sizeof(names) / sizeof(const char*); i++)
	{
		c.rm->setTileCoordinate(names[i], { {16 * i,0},{16,16} });
	}
	Terrain terter(SCREEN_WIDTH / TILE_SIZE, SCREEN_HEIGHT / TILE_SIZE);
	//test cyrano
	//Cyrano cyrano(terter.getEntry()[0]);

	//test enemyManager
	EnemyManager e_manager;
	sf::Clock clock;
	e_manager.newWave(&terter);

	//
	//Archer a(static_cast<Ground*>(terter.getTile(3, 0)), 0);
	//terter.addBuilding(&a);
	//

	//test BuildingManager
	BuildingManager b_manager(&terter);
	b_manager.addBuilding("Archer",static_cast<Ground*>(terter.getTile(3, 0)));
	b_manager.addBuilding("Canon",static_cast<Ground*>(terter.getTile(6, 0)));

	float fps_[100] = {};
	float fps=100;
	int fps_i = 0;

	clock.restart();
	while (win.isOpen())
	{
		while (const std::optional event = win.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				win.close();
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				win.setView(sf::View(sf::Vector2f(win.getView().getCenter()), sf::Vector2f(resized->size)));
			}
		}
		c.time+=( c.dt = clock.restart().asMilliseconds());
		e_manager.updateEnemies(c);
		b_manager.updateBuildings(c);
		win.clear(sf::Color::White);
		terter.draw(c);
		e_manager.draw(c);
		b_manager.draw(c);
		fps_[fps_i = (fps_i + 1) % 100]= 1000. / c.dt;
		if (!fps_i)
		{
			fps = 0;
			for (int i = 0; i < 100; i++)fps += fps_[i];
			fps /= 100.f;
		}
		std::ostringstream oss("");
		oss << "fps : " << (int)fps;
		t.setString(oss.str());
		c.rm->render(&win);
		win.draw(t);
		win.display();
	}
	return 0;
}