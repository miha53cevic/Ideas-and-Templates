#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class RougeLikeApp
{
public:
	RougeLikeApp();
	~RougeLikeApp();

	void setMapHeight(int l_height);
	void setMapWidth(int l_width);
	void setBlockSize(int l_blocksize);
	void setLevel(std::string l_level);

	void HandleInput();
	void Update();
	void Draw(sf::RenderWindow* window);

private:
	int m_mapWidth;
	int m_mapHeight;
	int m_blockSize;

	std::string m_level;

	enum Move {EMPTY ,UP, DOWN, LEFT, RIGHT};

	Move m_InputQueue;

	sf::Vector2i m_player;

	sf::RectangleShape wall;
	sf::CircleShape player;
};

