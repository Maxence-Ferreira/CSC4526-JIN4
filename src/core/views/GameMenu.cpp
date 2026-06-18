#include "GameMenu.h"

GameMenu::GameMenu(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed)
	:View(vm, rw, tileset, { {"continue",nullptr} }, seed)
{
	m_context.rm->setTileCoordinate("background", { {117,0},{796,448} });
}

void GameMenu::handle(const std::optional<sf::Event>& ev)
{
	if (const auto* resized = ev->getIf<sf::Event::Resized>())
	{
		int it = -m_gui_widget.size() / 2;
		for (auto& w : m_gui_widget)
		{
			w.second->setPosition(m_context.window->getSize().x / 2, m_context.window->getSize().y / 2 + 100 * it);
			it++;
		}
	}
	View::handle(ev);
}

void GameMenu::update()
{
}

void GameMenu::draw()
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


void GameMenu::reset()
{
}

