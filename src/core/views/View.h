#pragma once

#include "common.h"
#include "ViewManager.h"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <unordered_map>

class ViewManager;

class View
{
public:
	View(ViewManager* vm,sf::RenderWindow* rw, std::string tileset, const std::unordered_map<std::string, std::shared_ptr<View>>& navigator, unsigned int seed);
	virtual void handle(const std::optional<sf::Event>& ev);
	virtual void update();
	virtual void draw();
	virtual void reset() = 0;
	virtual ~View();
private:
protected:
	context m_context;
	ViewManager* m_manager;
	tgui::Gui m_gui;
	std::map<std::string, sf::Texture> m_gui_textures;
	std::map<std::string, std::shared_ptr<tgui::Button>> m_gui_widget;
	std::unordered_map<std::string, std::shared_ptr<View>> m_navigator;
};