#include "LoseMenu.h"

LoseMenu::LoseMenu(Game* game, ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed)
	:View(vm, rw, tileset, { "continue","quit"}, {nullptr,nullptr}, seed), m_font("resources/Cyrano.ttf"), m_text(m_font, "T'as perdu, \nJamais Roxane ne posera les yeux sur toi, \nJamais elle ne t'aimera.\nBien a toi\n\tCyrano", 50)
{
	m_text.setFillColor(sf::Color::Black);
	m_context.rm->setTileCoordinate("background", { {0,0},{810,448} });
	m_gui_widget["quit"]->onClick([this] {m_context.window->close(); });
}

void LoseMenu::handle(const std::optional<sf::Event>& ev)
{
	View::handle(ev);
}

void LoseMenu::update()
{
}

void LoseMenu::draw()
{
	float height = 448.f / 796.f * m_context.window->getSize().x;
	float width = 796.f / 448.f * m_context.window->getSize().y;
	width = std::max(width, (float)m_context.window->getSize().x);
	height = std::max(height, (float)m_context.window->getSize().y);
	const float x = (m_context.window->getSize().x - width) / 2.f;
	const float y = (m_context.window->getSize().y - height) / 2.f;
	m_context.rm->draw({ {x,y},{width,height} }, "background");
	m_context.rm->render(m_context.window);
	m_context.window->draw(m_text);
	View::draw();
}


void LoseMenu::reset()
{
}

bool LoseMenu::behavior(const std::string& action_name)
{
	return false;
}

