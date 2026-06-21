#include "Game.h"

#include "GameMenu.h"
#include "LoseMenu.h"

Game::Game(ViewManager* vm, sf::RenderWindow* rw, std::string tileset,
    int difficulty, unsigned int seed)
    : View(vm, rw, tileset, { "placeArcher", "placeCanon", "removeBuilding", "levelup" },
        { nullptr, nullptr, nullptr, nullptr }, seed),
    m_terrain(std::make_unique<Terrain>(rw->getSize().x / TILE_SIZE,
        rw->getSize().y / TILE_SIZE,
        difficulty, *m_context.rand)),
    m_building_manager(std::make_unique<BuildingManager>(m_terrain.get())),
    m_enemy_manager(std::make_unique<EnemyManager>(difficulty)),
    m_clock(),
    m_font("resources/Cyrano.ttf"),
    m_text_displayer(m_font),
    m_money_displayer(m_font),
    m_difficulty(difficulty),
    m_money(500) {
    m_building_manager->setTerrain(m_terrain.get());
    m_enemy_manager->newWave(m_terrain.get());
    m_building_manager->addBuilding(
        "Archer", static_cast<Ground*>(m_terrain->getTile(3, 0)));
    m_building_manager->addBuilding(
        "Canon", static_cast<Ground*>(m_terrain->getTile(6, 0)));
    m_building_manager->addBuilding(
        "Post", static_cast<Ground*>(m_terrain->getTile(
            m_terrain->getWidth() - 1, m_terrain->getHeight() / 2)));
    m_clock.restart();

    m_navigator["menu"] = std::make_shared<GameMenu>(
        this, vm, rw, "resources/mainmenu_tileset.png", seed);
    m_navigator["lose"] = std::make_shared<LoseMenu>(
        this, vm, rw, "resources/mainmenu_tileset.png", seed);
    for (const auto& name : m_ordered_id_views) {
        if (m_gui_widget[name] != nullptr) {
            auto lay = m_gui_widget[name]->getPositionLayout();
            lay.x = "100%";
            m_gui_widget[name]->setPosition(lay);
            m_gui_widget[name]->setOrigin(1, .5);
        }
    }

    std::vector<std::string> names{
        "post",          "archer",  "canon",         "outmap1",
        "outmap2",       "outmap3", "outmap4",       "ground1",
        "groundflower1", "ground2", "groundflower2", "ground3",
        "groundflower3", "ground4", "groundflower4", "path1",
        "path2",         "path3",   "path4",         "cyrano1",
        "cyrano2",       "dog1",    "dog2",          "firearm1",
        "firearm2",      "horse1",  "horse2",        "kamikaze1",
        "kamikaze2",     "melee1",  "melee2",        "canonball",
        "arrow",         "coin",    "white" };
    for (int i = 0; i < names.size(); i++)
        m_context.rm->setTileCoordinate(names[i], { {16 * i, 0}, {16, 16} });
}

void Game::update() {
    m_context.time += (m_context.dt = m_clock.restart().asMilliseconds());
    m_terrain->update(m_context);
    m_building_manager->update(m_context);
    m_enemy_manager->update(m_context);
    m_money += m_enemy_manager->collectBounties();
    if (m_terrain->countEnemyInPost() >= 10 - m_difficulty) {
        reset();
        m_manager->changeView(m_navigator["lose"]);
    }
}

void Game::draw() {
    static float fps_[100] = {};
    static float fps = 120;
    static int fps_i = 0;

    m_terrain->draw(m_context);
    m_building_manager->draw(m_context);
    m_enemy_manager->draw(m_context);

    sf::FloatRect textBounds(m_money_displayer.getLocalBounds());                               //dimension text
    const float textX = m_context.window->getView().getSize().x - textBounds.size.x - 20.0f;    //text fit to the end
    const float iconSize = 32.0f;
    const float iconX = textX - iconSize - 10.f;                                                //coin before text
    const float iconY = textBounds.position.y + (textBounds.size.y / 2.0f) - (iconSize / 2.0f);//align coin & text

    m_context.rm->draw({ {iconX + m_context.offsetX, iconY + m_context.offsetY}, {iconSize, iconSize} }, "coin");

    m_context.rm->render(m_context.window,
        { m_context.offsetX, m_context.offsetY });

	m_enemy_manager->drawWave(m_context);
    fps_[fps_i = (fps_i + 1) % 100] = 1000. / m_context.dt;
    if (!fps_i) {
        fps = 0;
        for (int i = 0; i < 100; i++) fps += fps_[i];
        fps /= 100.f;
    }
    std::ostringstream oss("");
    oss << "fps : " << (int)fps;
    m_text_displayer.setString(oss.str());
    m_text_displayer.setPosition(sf::Vector2f(10.0f, 0.0f));
    m_context.window->draw(m_text_displayer);

    // dessin de la piece avec la qté d'argent
    std::ostringstream oss1("");
    oss1 << (int)m_money;
    m_money_displayer.setString(oss1.str());

    // Placement et dessin du texte
    m_money_displayer.setPosition(sf::Vector2f(textX, 0));
    m_context.window->draw(m_money_displayer);


    View::draw();
}

void Game::onEnter() {
    m_manager->loopOn("resources/loop.ogg");
    m_context.mouseX = sf::Mouse::getPosition().x;
    m_context.mouseY = sf::Mouse::getPosition().y;
}

void Game::onExit() { m_manager->pauseMusic(); }

bool Game::behavior(const std::string& action_name) {
    if (action_name == "placeArcher") {
        int cost = m_building_manager->getPrice("Archer");
        if (m_money >= cost) {
            m_building_manager->planConstruct("Archer");
            m_money -= cost;
        }
        return true;
    }
    else if (action_name == "placeCanon") {
        int cost = m_building_manager->getPrice("Canon");
        if (m_money >= cost) {
            m_building_manager->planConstruct("Canon");
            m_money -= cost;
        }
        return true;
    }
    else if (action_name == "removeBuilding") {
        m_building_manager->planDestruct();
		int refunds = m_building_manager->collectRefunds();
    	if (m_difficulty <= 4) {
        	m_money += refunds;
   		}
		return true;
    } 
    else if (action_name == "levelup") {
        m_building_manager->levelUpBuilding();
        return true;
    }
    return false;
}

void Game::reset() {
    m_terrain = std::make_unique<Terrain>(
        m_context.window->getSize().x / TILE_SIZE,
        m_context.window->getSize().y / TILE_SIZE, m_difficulty, *m_context.rand);
    m_enemy_manager = std::make_unique<EnemyManager>(m_difficulty);
    m_enemy_manager->newWave(m_terrain.get());
    m_building_manager = std::make_unique<BuildingManager>(m_terrain.get());
    m_building_manager->addBuilding(
        "Archer", static_cast<Ground*>(m_terrain->getTile(3, 0)));
    m_building_manager->addBuilding(
        "Canon", static_cast<Ground*>(m_terrain->getTile(6, 0)));
    m_building_manager->addBuilding(
        "Post", static_cast<Ground*>(m_terrain->getTile(
            m_terrain->getWidth() - 1, m_terrain->getHeight() / 2)));
    m_clock.restart();
    m_money = 500;

    m_manager->stopMusic();
}

void Game::handle(const std::optional<sf::Event>& ev) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        m_manager->changeView(m_navigator["menu"]);
    else if (auto mev = ev->getIf<sf::Event::MouseMoved>()) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            m_context.offsetX -= mev->position.x - m_context.mouseX;
            m_context.offsetY -= mev->position.y - m_context.mouseY;
        }
        m_context.mouseX = mev->position.x;
        m_context.mouseY = mev->position.y;
    }

    View::handle(ev);
}
