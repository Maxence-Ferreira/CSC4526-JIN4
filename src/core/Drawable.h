#pragma once
#include "SFML/Graphics.hpp"
#include "Graphics/ResourceManager.h"
#include <random>

struct context
{
	unsigned int time;
	unsigned int dt;
	double offsetX, offsetY;
	sf::RenderWindow* window;
	std::unique_ptr<ResourceManager> rm;
	std::mt19937* rand;
};

class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void draw(const context& ctx)=0;
	virtual void update(const context& ctx){};
};