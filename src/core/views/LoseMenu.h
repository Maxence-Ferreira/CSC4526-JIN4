#pragma once
#include "View.h"
#include "Game.h"

class LoseMenu : public View
{
public:
	LoseMenu(Game* game, ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed);
	// H�rit� via View
	virtual void handle(const std::optional<sf::Event>& ev) override;
	virtual void update() override;
	virtual void draw() override;
	virtual void reset() override;
protected:
private:
	virtual bool behavior(const std::string& action_name) override;
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Texture m_img_tex;
    sf::Sprite m_img_sprite;
};