#include "game.h"

Game::Game()
{
	//Load Default settings && Textures
}
Game::Game(const sf::Vector2u& l_size, const std::string& l_name) : m_window(l_size, l_name) {}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::HandleInput()
{
	//input
	m_rougelikeapp.HandleInput();
}

void Game::Update()
{
	//Event System
	m_window.Update();


	//TickRate System
	float fFrameTime = 1.0f / 10.0f;

	if (m_elapsed.asSeconds() >= fFrameTime)
	{
		m_rougelikeapp.Update();

		m_elapsed -= sf::seconds(fFrameTime);
	}
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::White);
	
	m_rougelikeapp.Draw(m_window.getWindow());

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed += m_clock.restart();
}