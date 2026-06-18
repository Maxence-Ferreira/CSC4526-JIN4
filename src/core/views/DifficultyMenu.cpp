#include "DifficultyMenu.h"
#include "Game.h"

DifficultyMenu::DifficultyMenu(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed)
	:View(vm, rw, tileset,
		{
			"noob",
			"easy",
			"normal",
			"difficult",
			"hell"},
		{ 
			std::make_shared<Game>(vm,rw,"resources/tileset.png",2,seed) , 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 3, seed), 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 4, seed), 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 5, seed), 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 6, seed)
		}, 
		seed)
{
	m_context.rm->setTileCoordinate("background", { {117,0},{796,448} });
}

void DifficultyMenu::handle(const std::optional<sf::Event>& ev)
{
	View::handle(ev);
}

void DifficultyMenu::update()
{
}

void DifficultyMenu::draw()
{
	float height = 448.f / 796.f * m_context.window->getSize().x;
	float width = 796.f / 448.f * m_context.window->getSize().y;
	width = std::max(width, (float)m_context.window->getSize().x);
	height = std::max(height, (float)m_context.window->getSize().y);
	const float x = (m_context.window->getSize().x - width) / 2.f;
	const float y = (m_context.window->getSize().y - height) / 2.f;
	m_context.rm->draw({ {x,y},{width,height} }, "background");
	m_context.rm->render(m_context.window);
	View::draw();
}


void DifficultyMenu::reset()
{
}

