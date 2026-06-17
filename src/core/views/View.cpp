#include "View.h"

View::View(sf::RenderWindow* rw, std::string tileset, unsigned int seed) :m_context{
	.time = 0,
	.dt = 0,
	.offsetX = 0,
	.offsetY = 0,
	.window = rw,
	.rm = std::make_unique<ResourceManager>(tileset),
	.rand = std::make_unique<std::mt19937>(seed),
}
{
	//
}

bool View::isViewChange()
{
	if(m_next)return true;
	return false;
}

std::unique_ptr<View> View::nextView()
{
	std::unique_ptr<View> t = std::move(m_next);

	return t;
}

View::~View()=default;
