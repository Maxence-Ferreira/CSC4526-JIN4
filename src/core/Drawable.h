#pragma once
#include "SFML/Graphics.hpp"
#include "Graphics/ResourceManager.h"

struct context
{
	unsigned int time;
	unsigned int dt;
	double offsetX, offsetY;
	sf::RenderWindow* window;
	ResourceManager rm;
};

class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void draw(const context& ctx)=0;
	virtual void update(const context& ctx){};
};