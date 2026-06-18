#pragma once

#include "../common.h"
#include "View.h"
#include <vector>

class View;

class ViewManager
{
public:
	ViewManager(sf::RenderWindow* rw, unsigned int seed=42);
	void handle(const std::optional<sf::Event>& ev);
	void update();
	void draw();
	void changeView(std::shared_ptr<View> view);
	void backView();
private:
	std::shared_ptr<View> m_active_view;
	std::vector<std::shared_ptr<View>> m_views;
};