#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Panning and Zooming");

	sf::View view = window.getView();

	sf::RectangleShape rect(sf::Vector2f(1, 1));
	rect.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	rect.setFillColor(sf::Color::Blue);

	sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				view.move(sf::Vector2f(-10.f, 0.f));
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
			{
				view.move(sf::Vector2f(10.f, 0.f));
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
			{
				view.move(sf::Vector2f(0.f, -10.f));
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				view.move(sf::Vector2f(0.f, 10.f));
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			{
				view.zoom(0.5f);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				view.zoom(1.5f);
			}
		}

		window.setView(view);

		window.clear(sf::Color::Black);

		window.draw(background);
		window.draw(rect);

		window.display();
	}

	return 0;
}