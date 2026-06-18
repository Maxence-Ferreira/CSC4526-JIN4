#include "ViewManager.h"
#include "MainMenu.h"

ViewManager::ViewManager(sf::RenderWindow* rw, unsigned int seed) :m_active_view(std::make_shared<MainMenu>(this, rw, "resources/mainmenu_tileset.png", seed)), m_views{m_active_view}
{
}

void ViewManager::handle(const std::optional<sf::Event>& ev)
{
	if (!m_active_view)return;
	m_active_view->handle(ev);
}

void ViewManager::update()
{
	if (!m_active_view)return;
	m_active_view->update();
}
void ViewManager::draw()
{
	if (!m_active_view)return;
	m_active_view->draw();
}

void ViewManager::changeView(std::shared_ptr<View> view)
{
	m_active_view=view;
	m_views.push_back(m_active_view);
}

void ViewManager::backView()
{
	if (m_views.size()<=1)return;
	m_views.pop_back();
	m_active_view = m_views.back();
}
