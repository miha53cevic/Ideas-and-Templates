#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

class Bullet
{
public:
	Bullet(float r = 5.f)
	{
		shape.setRadius(r);
		shape.setFillColor(sf::Color::Green);

		fSpeed = 8.f;
	}

	sf::CircleShape shape;
	float fSpeed;
	sf::Vector2f currentVelocity;
	
};

int main()
{
	//Formule
	//	|a| = sqrt(x^2 + y^2)	|a| je MAGNITUDA, a ne absolute
	//	Normalize vector (vrijednosti mogu biti samo od 0 - 1)	U = a / |a|

	sf::RenderWindow window(sf::VideoMode(640, 480), "Vector Template SFML");
	window.setVerticalSyncEnabled(true);

	sf::CircleShape player(10.f);
	player.setFillColor(sf::Color::Red);

	std::vector<Bullet> vecBullets;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//	Update ======================

		//	Sredina kruga to jest playera ili prva tocka vektora -> a
		sf::Vector2f playerCenter = { player.getPosition().x + player.getRadius(),  player.getPosition().y + player.getRadius() };
		//	Pozicija misa ili druga tocka vektora -> a
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		//	Izracunali smo ax i ay od vektora -> a, pogledaj https://www.mathsisfun.com/algebra/vectors.html#magdir
		sf::Vector2f vektorA = mousePos - playerCenter;

		//	Normaliziraj vektora da ima vrijednosti od 0 - 1
		sf::Vector2f normaliziranVektorA = vektorA / sqrt(pow(vektorA.x, 2) + pow(vektorA.y, 2));

		//	Movemnt
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player.move(-5.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player.move(+5.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player.move(0.f, -5.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player.move(0.f, +5.f);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Bullet newBullet;
			newBullet.shape.setPosition(playerCenter);
			newBullet.currentVelocity = normaliziranVektorA * newBullet.fSpeed;

			vecBullets.push_back(newBullet);
		}

		for (auto &i : vecBullets)
		{
			i.shape.move(i.currentVelocity);
		}

		//printf("x = %f, y = %f\n", vektorA.x, vektorA.y);
		printf("x = %f, y = %f\n", normaliziranVektorA.x, normaliziranVektorA.y);

		//	Draw
		window.clear();

		window.draw(player);

		for (auto &i : vecBullets)
			window.draw(i.shape);

		window.display();
	}

	return 0;
}