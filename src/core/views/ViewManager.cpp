#include "ViewManager.h"
#include "MainMenu.h"

ViewManager::ViewManager(sf::RenderWindow* rw, unsigned int seed) :m_active_view(std::make_shared<MainMenu>(this, rw, "resources/mainmenu_tileset_sans_cyrano.png", seed)), m_views{m_active_view},
	m_music(),m_sounds(),m_music_name()
{
	m_active_view->onEnter();
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
	m_active_view->onExit();
	m_active_view=view;
	m_active_view->onEnter();
	m_views.push_back(m_active_view);
}

void ViewManager::backView()
{
	if (m_views.size()<=1)return;
	m_active_view->onExit();
	m_views.pop_back();
	m_active_view = m_views.back();
	m_active_view->onEnter();
}

void ViewManager::loopOn(std::string path)
{
	if (!(m_music && m_music_name == path))m_music = std::make_unique<sf::Music>(path);
	m_music->setLooping(true);
	m_music->play();
	m_music_name = path;
}

void ViewManager::playMusic(std::string path)
{
	if (!(m_music && m_music_name == path))m_music = std::make_unique<sf::Music>(path);
	m_music->setLooping(false);
	m_music->play();
	m_music_name = path;
}

void ViewManager::pauseMusic()
{
	if (m_music)m_music->pause();
}

void ViewManager::stopMusic()
{
	if (m_music)m_music->pause();
}

void ViewManager::playSound(std::string sound)
{
	if (m_sounds.find(sound) == m_sounds.end())
	{
		std::unique_ptr<sf::SoundBuffer> snd(std::make_unique< sf::SoundBuffer>(sound));
		m_sounds[sound] = { std::move(snd),std::make_unique<sf::Sound>(*snd) };
	}
	m_sounds[sound].second->play();
}
