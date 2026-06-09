#pragma once
#include "SFML/Graphics.hpp"

struct context
{
	unsigned int dt;
	double offsetX, offsetY;
	sf::RenderWindow* window;
	float animationTimer=0.f;
	float timePerFrame = 250.0f;
};

class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void draw(const context& ctx)=0;
	virtual void update(const context& ctx){};
};