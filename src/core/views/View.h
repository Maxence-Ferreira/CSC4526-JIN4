#pragma once

#include "common.h"


class View
{
public:
	View(sf::RenderWindow* rw, std::string tileset, unsigned int seed);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void reset() = 0;
	virtual ~View();
private:
protected:
	context m_context;
};