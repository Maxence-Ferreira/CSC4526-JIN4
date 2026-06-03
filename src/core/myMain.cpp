#include "myMain.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "map/Terrain.h"
#include "common.h"


using namespace std;
int myMain() {
	cout << "HW" << endl;
	sf::RenderWindow win(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)),"CMIUC");
	Terrain terter(SCREEN_WIDTH / TILE_SIZE, SCREEN_HEIGHT / TILE_SIZE);
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
		win.clear(sf::Color::White);
		terter.draw({0,0,0,&win});
		win.display();
	}
	return 0;
}