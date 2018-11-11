#include "game.h"
#include <iostream>

int main()
{
	Game game(sf::Vector2u(640, 480), "RougeLikeApp SFML Demo");

	while (!game.getWindow() -> IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}