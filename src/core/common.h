#pragma once
#define TILE_SIZE 50.f
#define SCREEN_WIDTH 1200u
#define SCREEN_HEIGHT 800u
#include "SFML/Graphics.hpp"

struct context
{
	unsigned int dt;
	double offsetX, offsetY;
	sf::RenderWindow* window;
};