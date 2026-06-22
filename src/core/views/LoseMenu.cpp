#include "LoseMenu.h"

LoseMenu::LoseMenu(Game* game, ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed)
	:View(vm, rw, tileset, { "continue","quit"}, {nullptr,nullptr}, seed), m_font("resources/Cyrano.ttf"), m_text(m_font, "T'as perdu, \nJamais Roxane ne posera les yeux sur toi, \nJamais elle ne t'aimera.\nBien a toi,\n\n\t\t\t\t\t\t\t\tCyrano", 50), m_img_sprite(m_img_tex)
{
	m_text.setFillColor(sf::Color::Black);
	m_context.rm->setTileCoordinate("background", { {0,0},{2483,1366} });
	m_gui_widget["quit"]->onClick([this] {m_context.window->close(); });

	if (m_img_tex.loadFromFile("resources/grandCyrano.png")) {
        m_img_sprite.setTextureRect(sf::IntRect({0, 0}, { (int)m_img_tex.getSize().x, (int)m_img_tex.getSize().y }));
    }
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
	float height = 1366.f / 2483.f * m_context.window->getSize().x;
	float width = 2483.f / 1366.f * m_context.window->getSize().y;
	width = std::max(width, (float)m_context.window->getSize().x);
	height = std::max(height, (float)m_context.window->getSize().y);
	const float x = (m_context.window->getSize().x - width) / 2.f;
	const float y = (m_context.window->getSize().y - height) / 2.f;
	m_context.rm->draw({ {x,y},{width,height} }, "background");
	m_context.rm->render(m_context.window);
	m_context.window->draw(m_text);

	sf::FloatRect textBounds = m_text.getLocalBounds();

    sf::RectangleShape bgRect;
    bgRect.setSize(sf::Vector2f(textBounds.size.x + (30.0f * 2.0f), textBounds.size.y + (30.0f * 2.0f)));
    bgRect.setFillColor(sf::Color(255, 255, 255, 255));

    float rectX = m_context.window->getSize().x - bgRect.getSize().x - 60.0f;
    float rectY = 60.0f;
    
    bgRect.setPosition(sf::Vector2f(rectX, rectY));

    m_text.setPosition(sf::Vector2f(rectX + 30.0f - textBounds.position.x, rectY + 30.0f - textBounds.position.y));

    m_context.window->draw(bgRect);
    m_context.window->draw(m_text);

  
    // 1. Calcul du centre exact de l'espace vide en bas
    float bottomOfRect = rectY + bgRect.getSize().y;
    float screenBottom = m_context.window->getSize().y;
    float emptySpaceCenterY = bottomOfRect + ((screenBottom - bottomOfRect) / 2.0f);
    
    // 2. Calcul du centre du rectangle blanc (pour l'alignement horizontal)
    float rectCenterX = rectX + (bgRect.getSize().x / 2.0f);
    
    // 3. Empilement : Même position X, positions Y décalées
    // (On recule X de 110 pixels pour centrer, car tes boutons font environ 220px de large)
    float buttonX = rectCenterX- 20.0f; 
    
    // On met "Continuer" juste au-dessus du centre visuel, et "Quitter" juste en dessous
    float buttonY_continue = emptySpaceCenterY - 80.0f; 
    float buttonY_quit     = emptySpaceCenterY + 40.0f; 

    // Application directe avec les positions calculées
    if (m_gui_widget["continue"]) {
        m_gui_widget["continue"]->setPosition(buttonX, buttonY_continue);
    }
    
    if (m_gui_widget["quit"]) {
        m_gui_widget["quit"]->setPosition(buttonX, buttonY_quit);
    }

	m_img_sprite.setScale(sf::Vector2f(4.0f,4.0f));
	float imgX = 60.0f;
    float imgY = m_context.window->getSize().y - m_img_sprite.getGlobalBounds().size.y - 60.0f;
	m_img_sprite.setPosition(sf::Vector2f(imgX, imgY));
	m_context.window->draw(m_img_sprite);

	View::draw();
}


void LoseMenu::reset()
{
}

bool LoseMenu::behavior(const std::string& action_name)
{
	return false;
}

