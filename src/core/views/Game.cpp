#include "Game.h"
#include "GameMenu.h"
#include "LoseMenu.h"

Game::Game(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, int difficulty, unsigned int seed) :
	View(vm, rw, tileset, {"placeArcher","placeCanon","removeBuilding" }, {nullptr,nullptr ,nullptr }, seed),
	m_terrain(std::make_unique<Terrain>(rw->getSize().x / TILE_SIZE, rw->getSize().y / TILE_SIZE, difficulty, *m_context.rand)),
	m_building_manager(std::make_unique<BuildingManager>(nullptr)),
	m_enemy_manager(std::make_unique<EnemyManager>(difficulty)),
	m_clock(),
	m_font("resources/Cyrano.ttf"),
	m_text_displayer(m_font),
	m_song("resources/loop.ogg"),
	m_difficulty(difficulty)
{
	m_building_manager->setTerrain(m_terrain.get());
	m_enemy_manager->newWave(m_terrain.get());
	m_building_manager->addBuilding("Archer", static_cast<Ground*>(m_terrain->getTile(3, 0)));
	m_building_manager->addBuilding("Canon", static_cast<Ground*>(m_terrain->getTile(6, 0)));
	m_building_manager->addBuilding("Post", static_cast<Ground*>(m_terrain->getTile(m_terrain->getWidth() - 1, m_terrain->getHeight() / 2)));
	m_clock.restart();

	m_navigator["menu"] = std::make_shared<GameMenu>(this, vm, rw, "resources/mainmenu_tileset.png", seed);
	m_navigator["lose"] = std::make_shared<LoseMenu>(this, vm, rw, "resources/mainmenu_tileset.png", seed);
	for (const auto& name : m_ordered_id_views)
	{
		auto lay = m_gui_widget[name]->getPositionLayout();
		lay.x = "100%";
		m_gui_widget[name]->setPosition(lay);
		m_gui_widget[name]->setOrigin(1,.5);
	}

	std::vector<std::string> names{
		"post",
		"archer",
		"canon",
		"outmap1",
		"outmap2",
		"outmap3",
		"outmap4",
		"ground1",
		"groundflower1",
		"ground2",
		"groundflower2",
		"ground3",
		"groundflower3",
		"ground4",
		"groundflower4",
		"path1",
		"path2",
		"path3",
		"path4",
		"cyrano1",
		"cyrano2",
		"dog1",
		"dog2",
		"firearm1",
		"firearm2",
		"horse1",
		"horse2",
		"kamikaze1",
		"kamikaze2",
		"melee1",
		"melee2",
		"canonball",
		"arrow",
		"coin",
		"white"
	};
	for (int i = 0; i < names.size(); i++)
		m_context.rm->setTileCoordinate(names[i], { {16 * i,0},{16,16} });
}


void Game::update()
{
	m_context.time += (m_context.dt = m_clock.restart().asMilliseconds());
	m_terrain->update(m_context);
	m_building_manager->update(m_context);
	m_enemy_manager->update(m_context);
	if (m_terrain->countEnemyInPost() >= 10 - m_difficulty)
	{
		reset();
		m_manager->changeView(m_navigator["lose"]);
	}
}

void Game::draw()
{
	static float fps_[100] = {};
	static float fps = 120;
	static int fps_i = 0;

	m_terrain->draw(m_context);
	m_building_manager->draw(m_context);
	m_enemy_manager->draw(m_context);
	m_context.rm->render(m_context.window, {m_context.offsetX, m_context.offsetY});
	m_enemy_manager->drawWave(m_context);
	
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
	View::draw();
}

void Game::onEnter()
{
	m_song.setLooping(true);
	m_song.play();
	m_context.mouseX = sf::Mouse::getPosition().x;
	m_context.mouseY = sf::Mouse::getPosition().y;
}

void Game::onExit()
{
	m_song.pause();
}

bool Game::behavior(const std::string& action_name)
{
	if (action_name == "placeArcher")
	{
		m_building_manager->planConstruct("Archer");
		return true;
	}
	else if (action_name == "placeCanon")
	{
		m_building_manager->planConstruct("Canon");
		return true;
	}
	else if (action_name == "removeBuilding")
	{
		std::cout << "Le joueur veut retirer un batiment" << std::endl;
		return true;
	}
	return false;
}

void Game::reset()
{
	m_terrain = std::make_unique<Terrain>(m_context.window->getSize().x / TILE_SIZE, m_context.window->getSize().y / TILE_SIZE, m_difficulty, *m_context.rand);
	m_enemy_manager = std::make_unique<EnemyManager>(m_difficulty);
	m_enemy_manager->newWave(m_terrain.get());
	m_building_manager = std::make_unique < BuildingManager>(m_terrain.get());
	m_building_manager->addBuilding("Archer", static_cast<Ground*>(m_terrain->getTile(3, 0)));
	m_building_manager->addBuilding("Canon", static_cast<Ground*>(m_terrain->getTile(6, 0)));
	m_building_manager->addBuilding("Post", static_cast<Ground*>(m_terrain->getTile(m_terrain->getWidth() - 1, m_terrain->getHeight() / 2)));
	m_clock.restart();
	
	m_song.stop();
}

void Game::handle(const std::optional<sf::Event>& ev)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))m_manager->changeView(m_navigator["menu"]);
	else if (auto mev = ev->getIf< sf::Event::MouseMoved>())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			m_context.offsetX -= mev->position.x - m_context.mouseX;
			m_context.offsetY -= mev->position.y - m_context.mouseY;
		}
		m_context.mouseX = mev->position.x;
		m_context.mouseY = mev->position.y;
	}
		
	View::handle(ev);
}
