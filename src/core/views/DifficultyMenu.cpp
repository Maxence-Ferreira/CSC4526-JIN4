#include "DifficultyMenu.h"
#include "Game.h"

DifficultyMenu::DifficultyMenu(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed)
	:View(vm, rw, tileset,
		{
			"noob",
			"easy",
			"normal",
			"difficult",
			"hell",
			"back"},
		{ 
			std::make_shared<Game>(vm,rw,"resources/tileset.png",2,seed) , 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 3, seed), 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 4, seed), 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 5, seed), 
			std::make_shared<Game>(vm, rw, "resources/tileset.png", 6, seed),
			nullptr
		}, 
		seed), m_img_sprite(m_img_tex)
{
	m_context.rm->setTileCoordinate("background", { {0,0},{2483,1366} });

	if (m_img_tex.loadFromFile("resources/grandCyrano.png")) {
        m_img_sprite.setTextureRect(sf::IntRect({0, 0}, { (int)m_img_tex.getSize().x, (int)m_img_tex.getSize().y }));
    }
}

void DifficultyMenu::handle(const std::optional<sf::Event>& ev)
{
	View::handle(ev);
}

void DifficultyMenu::update()
{
}

void DifficultyMenu::onEnter()
{
	m_manager->loopOn("resources/mieloreille.mp3");
}

void DifficultyMenu::onExit()
{
	m_manager->pauseMusic();
}
void DifficultyMenu::draw()
{
	float height = 1366.f / 2483.f * m_context.window->getSize().x;
	float width = 2483.f / 1366.f * m_context.window->getSize().y;
	width = std::max(width, (float)m_context.window->getSize().x);
	height = std::max(height, (float)m_context.window->getSize().y);
	const float x = (m_context.window->getSize().x - width) / 2.f;
	const float y = (m_context.window->getSize().y - height) / 2.f;
	m_context.rm->draw({ {x,y},{width,height} }, "background");
	m_context.rm->render(m_context.window);

	m_img_sprite.setScale(sf::Vector2f(4.0f,4.0f));
	float imgX = 60.0f;
    float imgY = m_context.window->getSize().y - m_img_sprite.getGlobalBounds().size.y - 60.0f;
	m_img_sprite.setPosition(sf::Vector2f(imgX, imgY));
	m_context.window->draw(m_img_sprite);

	View::draw();
}


void DifficultyMenu::reset()
{
}

bool DifficultyMenu::behavior(const std::string& action_name)
{
	return false;
}

