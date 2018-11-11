#pragma once
#include "window.h"
#include "RougeLikeApp.h"

class Game
{
public:
	Game();
	Game(const sf::Vector2u& l_size, const std::string& l_name);
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* getWindow();

	void RestartClock();

private:
	Window m_window;

	RougeLikeApp m_rougelikeapp;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};