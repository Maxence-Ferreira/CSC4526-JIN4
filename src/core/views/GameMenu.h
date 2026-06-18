#pragma once
#include "View.h"
#include "Game.h"

class GameMenu : public View
{
public:
	GameMenu(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed);
	// Hérité via View
	virtual void handle(const std::optional<sf::Event>& ev) override;
	virtual void update() override;
	virtual void draw() override;
	virtual void reset() override;
protected:
private:
};