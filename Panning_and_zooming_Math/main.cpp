#include <iostream>

#include "mihaSimpleSFML.h"
#include "util.h"

class PanningAndZooming : public mihaSimpleSFML
{
public:
	PanningAndZooming() {}

private:
	sf::Vector2i PanStart;
	sf::Vector2f Offset;
	sf::Vector2f Scale;

	void ScreenToWorld(sf::Vector2f screen, sf::Vector2f& world)
	{
		world.x = screen.x / Scale.x + Offset.x;
		world.y = screen.y / Scale.y + Offset.y;
	}

	void WorldToScreen(sf::Vector2f world, sf::Vector2f& screen)
	{
		screen.x = (world.x - Offset.x) * Scale.x;
		screen.y = (world.y - Offset.y) * Scale.y;
	}

	// Using Vector2i
	void ScreenToWorld(sf::Vector2i screen, sf::Vector2i& world)
	{
		world.x = screen.x / Scale.x + Offset.x;
		world.y = screen.y / Scale.y + Offset.y;
	}

	void WorldToScreen(sf::Vector2i world, sf::Vector2i& screen)
	{
		screen.x = (world.x - Offset.x) * Scale.x;
		screen.y = (world.y - Offset.y) * Scale.y;
	}

protected:
	bool virtual OnUserCreate()
	{
		Offset.x = -ScreenWidth() / 2;
		Offset.y = -ScreenHeight() / 2;

		Scale.x = 1.0f;
		Scale.y = 1.0f;

		return true;
	}

	void virtual Event(sf::Event e)
	{
		if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
		{
			PanStart = sf::Mouse::getPosition(*getWindow());
		}
	}

	bool virtual OnUserUpdate(sf::Time elapsed)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*getWindow());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Offset.x -= (mousePos.x - PanStart.x) / Scale.x;
			Offset.y -= (mousePos.y - PanStart.y) / Scale.y;

			PanStart.x = mousePos.x;
			PanStart.y = mousePos.y;
		}

		sf::Vector2i beforeZoomMouse;
		ScreenToWorld(mousePos, beforeZoomMouse);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			Scale *= 0.99f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			Scale *= 1.01f;
		}

		// Zoom offset vector jer inace zoomira od 0,0
		sf::Vector2i afterZoomMouse;
		ScreenToWorld(mousePos, afterZoomMouse);
		Offset.x += beforeZoomMouse.x - afterZoomMouse.x;
		Offset.y += beforeZoomMouse.y - afterZoomMouse.y;
		

		// Horizontal lines
		for (float y = 0.0f; y <= 100.0f; y++)
		{
				sf::Vector2f s(0.0f, y);
				sf::Vector2f e(100.0f, y);

				sf::Vector2f start_pixel;
				sf::Vector2f end_pixel;

				WorldToScreen(s, start_pixel);
				WorldToScreen(e, end_pixel);

				line newLine(start_pixel, end_pixel, sf::Color::White);
				Draw(*newLine.getLine());
		}

		// Vertical lines
		for (float x = 0.0f; x <= 100.0f; x++)
		{
			sf::Vector2f s(x, 0.0f);
			sf::Vector2f e(x, 100.0f);

			sf::Vector2f start_pixel;
			sf::Vector2f end_pixel;

			WorldToScreen(s, start_pixel);
			WorldToScreen(e, end_pixel);

			line newLine(start_pixel, end_pixel, sf::Color::White);
			Draw(*newLine.getLine());
		}

		return true;
	}
};

int main(int argc, char* argv[])
{
	PanningAndZooming demo;
	demo.Construct(1280, 720, L"PanningAndZooming");
	demo.Start();

	return 0;
}