#pragma once

#include "../common.h"
#include "View.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

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
	void loopOn(std::string path);
	void playMusic(std::string path);
	void pauseMusic();
	void stopMusic();
	void playSound(std::string sound);
private:
	std::shared_ptr<View> m_active_view;
	std::vector<std::shared_ptr<View>> m_views;
	std::unique_ptr<sf::Music> m_music;
	std::string m_music_name;
	std::map<std::string, std::pair<std::unique_ptr<sf::SoundBuffer>,std::unique_ptr<sf::Sound>>> m_sounds;
};