#include "MainMenu.h"

#include "DifficultyMenu.h"
#include "Game.h"
#include <fstream>
MainMenu::MainMenu(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed)
	:View(vm, rw, tileset, { "continue","new" ,"quit" }, { 0, std::make_shared<DifficultyMenu>(vm,rw,tileset,seed),0}, seed), m_img_sprite(m_img_tex), m_titre_sprite(m_titre_tex)
{
	m_context.rm->setTileCoordinate("background", { {0,0},{2483,1366} });
	m_gui_widget["quit"]->onClick([this] {m_context.window->close(); });

	/*
	if (std::ifstream f = std::ifstream("resources/save.json"))
		m_navigator["continue"]=std::make_shared<Game>(vm, rw, json::parse(f),seed);
		*/

	if (m_img_tex.loadFromFile("resources/grandCyrano.png")) {
		m_img_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)m_img_tex.getSize().x, (int)m_img_tex.getSize().y }));
	}
	if (m_titre_tex.loadFromFile("resources/logo_sans_nez.png")) {
		m_titre_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)m_titre_tex.getSize().x, (int)m_titre_tex.getSize().y }));
	}
}

void MainMenu::handle(const std::optional<sf::Event>& ev)
{
	View::handle(ev);
}

void MainMenu::update()
{
}

void MainMenu::draw()
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

	m_titre_sprite.setScale(sf::Vector2f(.5f,.5f));
	float titreX = (m_context.window->getSize().x - m_titre_sprite.getGlobalBounds().size.x) / 2.0f;
    float titreY = 20.0f;
	m_titre_sprite.setPosition(sf::Vector2f(titreX, titreY));
	m_context.window->draw(m_titre_sprite);

    float bottomOfTitle = titreY + m_titre_sprite.getGlobalBounds().size.y;
    float screenBottom = m_context.window->getSize().y;
    float emptySpaceCenterY = bottomOfTitle + ((screenBottom - bottomOfTitle) / 2.0f)-40.0f;
 
    float buttonX = m_context.window->getSize().x / 2.0f ; 
    
    float buttonY_continue = emptySpaceCenterY - 90.0f; 
	float buttonY_new = emptySpaceCenterY; 
    float buttonY_quit = emptySpaceCenterY + 90.0f; 

    if (m_gui_widget["continue"]) {
        m_gui_widget["continue"]->setPosition(buttonX, buttonY_continue);
    }

	if (m_gui_widget["new"]) {
        m_gui_widget["new"]->setPosition(buttonX, buttonY_new);
    }
    
    if (m_gui_widget["quit"]) {
        m_gui_widget["quit"]->setPosition(buttonX, buttonY_quit);
    }

	View::draw();
}


void MainMenu::reset()
{
}

void MainMenu::onEnter()
{
	m_manager->loopOn("resources/mieloreille.mp3");
}

void MainMenu::onExit()
{
	m_manager->pauseMusic();
}

bool MainMenu::behavior(const std::string& action_name)
{
	return false;
}

