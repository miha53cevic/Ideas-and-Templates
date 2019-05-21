#pragma once
#include "mihaSimpleSFML.h"
#include <SFML/Network.hpp>
#include <iostream>

class client : public mihaSimpleSFML
{
public:
	client() {}

    ~client() 
    {
        // when existing send error code 404 to server so it shutsdown
        sf::Packet data;
        data << 4.04f;
        connection.send(data, "localhost", 5003);

        connection.unbind();
    }

private:
    sf::UdpSocket connection;

    sf::CircleShape ball;
    sf::RectangleShape player;

    sf::IpAddress adress = "localhost";
    unsigned short int port = 5003;

    sf::Vector2f lastSentPos;

protected:
	virtual bool OnUserCreate() override
	{
        // Try openning connection
        if (connection.bind(5001) != sf::Socket::Done)
        {
            // Error
            std::cout << "Failed to start client connection!\n";
        }
        else
        {
            std::cout << "Opened Client connection!\n";

            // Send a packet to the server and wait for response
            sf::Packet data;
            data << 0;
            connection.send(data, adress, port);

            // Response
            data.clear();
            connection.receive(data, adress, port);

            int x;
            data >> x;

            if (x == 200)
                std::cout << "Client succesfully connected to server!\n";

            // Make it so it doesn't wait constantly for packets it either gets them or it doesn't
            connection.setBlocking(false);
        }
        
        // Setup game
        ball.setFillColor(sf::Color::White);
        ball.setRadius(10.0f);
        ball.setOrigin(ball.getRadius(), ball.getRadius());
        ball.setPosition(ScreenWidth() / 2, ScreenHeight() / 2);
 
        player.setFillColor(sf::Color::White);
        player.setSize(sf::Vector2f(20, 100));

		return true;
	}

	virtual bool OnUserUpdate(sf::Time elapsed) override
	{
        // Send data to server
        sf::Packet data;
        data << player.getPosition().x, player.getPosition().y;

        connection.send(data, adress, port);

        // Receive ball position from server
        data.clear();

        connection.receive(data, adress, port);

        float x, y;
        if (data >> x)
        {
            ball.setPosition(x, ball.getPosition().y);

            if (data >> y)
            {
                ball.setPosition(ball.getPosition().x, y);
            }
        }

        // Controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.move(0, -100.0f * elapsed.asSeconds());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.move(0, 100.0f * elapsed.asSeconds());
        }

        // Drawing routines
        Draw(ball);
        Draw(player);

		return true;
	}

};

int main()
{
    client app;
    app.Construct(640, 480, L"Client");
    app.Start();

    return 0;
}