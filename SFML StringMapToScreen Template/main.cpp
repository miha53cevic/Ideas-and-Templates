#include <SFML/Graphics.hpp>
#include <string>

int main()
{
	sf::RenderWindow window(sf::VideoMode(480, 360), "SFML works!");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Initialization
		std::string level;

		sf::RectangleShape rect;

		int Width = 28;
		int Height = 10;

		int BlockSize = 16;

		//OnCreate
		level += "############################";
		level += "#..........................#";
		level += "#..........................#";
		level += "#..........................#";
		level += "#..........................#";
		level += "#..........................#";
		level += "#..........................#";
		level += "#..........................#";
		level += "#..........................#";
		level += "############################";

		rect.setFillColor(sf::Color::Color(125, 125, 125));
		rect.setSize(sf::Vector2f(BlockSize, BlockSize));

		//OnUpdate

		window.clear();
		
		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Height; y++)
			{
				switch (level[(y * Width) + x])
				{
				case '#':
				{
					rect.setPosition(x * BlockSize, y * BlockSize);
					window.draw(rect);
					break;
				}
				}
			}
		}
		
		window.display();
	}

	return 0;
}