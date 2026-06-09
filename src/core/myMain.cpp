#include "myMain.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "map/Terrain.h"
#include "common.h"
#include "enemy/Cyrano.h"



using namespace std;
int myMain() {
	cout << "HW" << endl;
	sf::RenderWindow win(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)),"CMIUC");
	context c = {
		.dt=0,
		.offsetX=0,
		.offsetY=0,
		.window=&win
	};
	Terrain terter(SCREEN_WIDTH / TILE_SIZE, SCREEN_HEIGHT / TILE_SIZE);
	//test cyrano
	Cyrano cyrano(terter.getEntry()[0]);
	sf::Clock clock;

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
		c.dt = clock.restart().asMilliseconds();
		cyrano.update(c);
		win.clear(sf::Color::White);
		terter.draw(c);
		cyrano.draw(c);
		win.display();
	}
	return 0;
}