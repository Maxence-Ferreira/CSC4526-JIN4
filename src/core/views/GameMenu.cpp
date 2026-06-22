#include "GameMenu.h"

GameMenu::GameMenu(Game* game, ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed)
	:View(vm, rw, tileset, { "continue" , "save", "quit"}, {nullptr,nullptr,nullptr}, seed),m_game(game), m_img_sprite(m_img_tex)
{
	m_context.rm->setTileCoordinate("background", { {0,0},{2483,1366} });
	m_gui_widget["quit"]->onClick([this] {m_context.window->close(); });

	if (m_img_tex.loadFromFile("resources/grandCyrano.png")) {
        m_img_sprite.setTextureRect(sf::IntRect({0, 0}, { (int)m_img_tex.getSize().x, (int)m_img_tex.getSize().y }));
    }
}

void GameMenu::handle(const std::optional<sf::Event>& ev)
{
	View::handle(ev);
}

void GameMenu::update()
{
}

void GameMenu::draw()
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


void GameMenu::reset()
{
}

bool GameMenu::behavior(const std::string& action_name)
{
	if (action_name == "save")
	{
		std::cout << "le joueur sauvegarde" << std::endl;
		m_game->save();
		return true;
	}
	return false;
}

