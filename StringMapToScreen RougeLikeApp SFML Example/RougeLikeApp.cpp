#include "RougeLikeApp.h"

RougeLikeApp::RougeLikeApp()
{
	m_mapWidth = 15;
	m_mapHeight = 10;
	
	m_blockSize = 16;

	m_level += "###############";
	m_level += "#.............#";
	m_level += "#.............#";
	m_level += "#.............#";
	m_level += "#.............#";
	m_level += "#.............#";
	m_level += "#.........#...#";
	m_level += "#.............#";
	m_level += "#.............#";
	m_level += "###############";

	m_player = sf::Vector2i(m_mapWidth / 2, m_mapHeight / 2);
	m_level[(m_player.y * m_mapWidth) + m_player.x] = '*';

	wall.setFillColor(sf::Color::Color(125, 125, 125));
	wall.setSize(sf::Vector2f(m_blockSize, m_blockSize));
	
	player.setFillColor(sf::Color::Red);
	player.setRadius(m_blockSize / 2);
}
RougeLikeApp::~RougeLikeApp() {}

void RougeLikeApp::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_InputQueue = LEFT;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_InputQueue = RIGHT;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_InputQueue = UP;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_InputQueue = DOWN;
	else m_InputQueue = EMPTY;
}

void RougeLikeApp::Update()
{
	//Movement System
	if (m_InputQueue != EMPTY)
	{
		//Delete last Player pos
		m_level[(m_player.y * m_mapWidth) + m_player.x] = '.';

		switch (m_InputQueue)
		{
		case LEFT:
			if (m_level[(m_player.y * m_mapWidth) + m_player.x - 1] == '.')
				m_player.x--;
			break;
		case RIGHT:
			if (m_level[(m_player.y * m_mapWidth) + m_player.x + 1] == '.')
				m_player.x++;
			break;
		case UP:
			if (m_level[((m_player.y - 1) * m_mapWidth) + m_player.x] == '.')
				m_player.y--;
			break;
		case DOWN:
			if (m_level[((m_player.y + 1) * m_mapWidth) + m_player.x] == '.')
				m_player.y++;
			break;
		}
		m_InputQueue = EMPTY;

		//Set New Player Pos
		m_level[(m_player.y * m_mapWidth) + m_player.x] = '*';
	}
}

void RougeLikeApp::Draw(sf::RenderWindow* window)
{
	for (int x = 0; x < m_mapWidth; x++)
	{
		for (int y = 0; y < m_mapHeight; y++)
		{
			switch (m_level[(y * m_mapWidth) + x])
			{
			case '#':
				wall.setPosition(x * m_blockSize, y * m_blockSize);
				window->draw(wall);
				break;

			case '*':
				player.setPosition(x * m_blockSize, y * m_blockSize);
				window->draw(player);
				break;
			}
		}
	}
}

void RougeLikeApp::setMapHeight(int l_height) { m_mapHeight = l_height; }
void RougeLikeApp::setMapWidth(int l_width) { m_mapWidth = l_width; }
void RougeLikeApp::setBlockSize(int l_blocksize) { m_blockSize = l_blocksize; }
void RougeLikeApp::setLevel(std::string l_level) { m_level = l_level; }
