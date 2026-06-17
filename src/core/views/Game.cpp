#include "Game.h"

Game::Game(sf::RenderWindow* rw, std::string tileset, int difficulty, unsigned int seed):
	View(rw,tileset,seed),
	m_terrain(rw->getSize().x/TILE_SIZE, rw->getSize().y / TILE_SIZE, difficulty, *m_context.rand),
	m_building_manager(&m_terrain),
	m_enemy_manager(),
	m_clock(),
	m_font("resources/Cyrano.ttf"),
	m_text_displayer(m_font)
{
	m_enemy_manager.newWave(&m_terrain);
	m_building_manager.addBuilding("Archer", static_cast<Ground*>(m_terrain.getTile(3, 0)));
	m_building_manager.addBuilding("Canon", static_cast<Ground*>(m_terrain.getTile(6, 0)));
	m_building_manager.addBuilding("Post", static_cast<Ground*>(m_terrain.getTile(m_terrain.getWidth() - 1, m_terrain.getHeight() / 2)));
	m_clock.restart();
}

void Game::setTileNames(const std::vector<std::string>& names)
{
	for (int i = 0; i < names.size(); i++)
		m_context.rm->setTileCoordinate(names[i], { {16 * i,0},{16,16} });
}

void Game::update()
{
	m_context.time += (m_context.dt = m_clock.restart().asMilliseconds());
	m_terrain.update(m_context);
	m_building_manager.update(m_context);
	m_enemy_manager.update(m_context);
}

void Game::draw()
{
	static float fps_[100] = {};
	static float fps = 120;
	static int fps_i = 0;

	m_terrain.draw(m_context);
	m_building_manager.draw(m_context);
	m_enemy_manager.draw(m_context);
	m_context.rm->render(m_context.window);

	fps_[fps_i = (fps_i + 1) % 100] = 1000. / m_context.dt;
	if (!fps_i)
	{
		fps = 0;
		for (int i = 0; i < 100; i++)fps += fps_[i];
		fps /= 100.f;
	}
	std::ostringstream oss("");
	oss << "fps : " << (int)fps;
	m_text_displayer.setString(oss.str());
	m_context.window->draw(m_text_displayer);
}

void Game::reset()
{
}
