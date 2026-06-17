#include "myMain.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "views/Game.h"
#include <sstream>

using namespace std;

int myMain() {
	sf::RenderWindow win(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), "Post Me If You Can");
	win.setFramerateLimit(120);
	
	Game game(&win, "resources/tileset.png",5,42);

	game.setTileNames({
		"post",
		"archer",
		"canon",
		"ground1",
		"groundflower1",
		"ground2",
		"groundflower2",
		"ground3",
		"groundflower3",
		"ground4",
		"groundflower4",
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
		"canonball",
		"arrow" });

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
		game.update();
		win.clear(sf::Color::White);
		game.draw();
		win.display();
	}
	return 0;
}