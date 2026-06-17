#pragma once

#include "views/View.h"
#include <TGUI/Backend/SFML-Graphics.hpp>

class MainMenu : public View
{
public:
	MainMenu(sf::RenderWindow* rw, std::string tileset, unsigned int seed);
	// Hérité via View
	virtual void update() override;
	virtual void draw() override;
protected:
private:
	tgui::Gui m_gui;

};