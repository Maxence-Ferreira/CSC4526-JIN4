#pragma once
#include "View.h"
#include "Game.h"

class LoseMenu : public View
{
public:
	LoseMenu(Game* game, ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed);
	// Hérité via View
	virtual void handle(const std::optional<sf::Event>& ev) override;
	virtual void update() override;
	virtual void draw() override;
	virtual void reset() override;
protected:
private:
	sf::Font m_font;
	sf::Text m_text;
};