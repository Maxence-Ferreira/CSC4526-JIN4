#pragma once
#include "SFML/Graphics.hpp"

struct context
{
	unsigned int dt;
	double offsetX, offsetY;
	sf::RenderWindow* window;
};

class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void draw(const context& ctx)=0;
	virtual void update(const context& ctx){};
};