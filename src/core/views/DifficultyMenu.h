#pragma once

#include "views/View.h"

class DifficultyMenu : public View
{
public:
	DifficultyMenu(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, unsigned int seed);
	// Hérité via View
	virtual void handle(const std::optional<sf::Event>& ev) override;
	virtual void update() override;
	virtual void draw() override;
	virtual void reset() override;
protected:
private:
	virtual bool behavior(const std::string& action_name) override;
};