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
	cout << "HW" << endl;
	sf::RenderWindow win(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)),"CMIUC");
	sf::Font f("resources/ARIAL.TTF");
	sf::Text t(f);
	context c = {
		.time = 0,
		.dt = 0,
		.offsetX = 0,
		.offsetY = 0,
		.window = &win,
		.rm = std::make_unique<ResourceManager>("resources/tileset.png", std::unordered_map<std::string,sf::IntRect>{
			{"archer",sf::IntRect{{0,0},{16,16}}},
			{"canon",sf::IntRect{{16,0},{16,16}}},
			{"ground",sf::IntRect{{32,0},{16,16}}},
			{"path",sf::IntRect{{48,0},{16,16}}},
			{"cyrano1",sf::IntRect{{64,0},{16,16}}},
			{"cyrano2",sf::IntRect{{80,0},{16,16}}},
			{"dog1",sf::IntRect{{96,0},{16,16}}},
			{"dog2",sf::IntRect{{112,0},{16,16}}},
			{"firearm1",sf::IntRect{{128,0},{16,16}}},
			{"firearm2",sf::IntRect{{144,0},{16,16}}},
			{"horse1",sf::IntRect{{160,0},{16,16}}},
			{"horse2",sf::IntRect{{176,0},{16,16}}},
			{"kamikaze1",sf::IntRect{{192,0},{16,16}}},
			{"kamikaze2",sf::IntRect{{208,0},{16,16}}},
			{"melee1",sf::IntRect{{224,0},{16,16}}},
			{"melee2",sf::IntRect{{240,0},{16,16}}},
			}),
	};
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
		c.rm->render(&win);
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
		oss << "fps : " << fps;
		t.setString(oss.str());
		win.draw(t);
		win.display();
	}
	return 0;
}