#pragma once
#include <SFML/Graphics.hpp>
class line
{
public:
	line(sf::Vector2f a, sf::Vector2f b, sf::Color c)
		: m_line(sf::PrimitiveType::Lines)
	{
		m_line.append(sf::Vertex(a, c));
		m_line.append(sf::Vertex(b, c));
	}

	sf::VertexArray* getLine() { return &m_line; }

private:
	sf::VertexArray m_line;
};