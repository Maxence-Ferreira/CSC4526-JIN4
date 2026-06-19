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
	View(ViewManager* vm,sf::RenderWindow* rw, std::string tileset, const std::vector<std::string>& id_view, const std::vector<std::shared_ptr<View>>& views, unsigned int seed);
	virtual void handle(const std::optional<sf::Event>& ev);
	virtual void update();
	virtual void draw();
	virtual void onEnter();
	virtual void onExit();
	virtual void reset() = 0;
	virtual ~View();
private:
	virtual bool behavior(const std::string& action) = 0;
protected:
	context m_context;
	ViewManager* m_manager;
	tgui::Gui m_gui;
	std::vector<std::string> m_ordered_id_views;
	std::map<std::string, sf::Texture> m_gui_textures;
	std::map<std::string, std::shared_ptr<tgui::Button>> m_gui_widget;
	std::unordered_map<std::string, std::shared_ptr<View>> m_navigator;
};