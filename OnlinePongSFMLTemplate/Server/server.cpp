#include "server.hpp"
#include <iostream>
#include <cmath>

#include "../Client/mihaSimpleSFML.h"

Server::Server()
{
    m_isRunning = true;

    // Listen for connections on a specified port
    if (m_socket.bind(5003) != sf::Socket::Done)
    {
        // Error
        std::cout << "Failed starting server!\n";
    }

    // Make it not block the program execution
    m_socket.setBlocking(false);

    // Starting game variables
    m_ballPos = { 320, 240 };
    m_playerPos = { 0, 240 };

    m_velocity.x = cosf(toRadian(45));
    m_velocity.y = sinf(toRadian(45));
}

Server::~Server()
{
    m_socket.unbind();
}

void Server::run()
{
    std::cout << "Running server!\n";

    bool ClientConnected = false;

    while (m_isRunning)
    {
        // Wait for players
        while (!ClientConnected)
        {
            sf::Packet data;
            sf::IpAddress adress;
            unsigned short int port;

            m_socket.receive(data, adress, port);

            int x;
            if (data >> x)
            {
                if (x == 0)
                {
                    // Send back reply
                    data.clear();
                    data << 200;
                    m_socket.send(data, adress, port);

                    std::cout << "Player connected!\n";

                    ClientConnected = true;
                }
            }

            // Otherwise if the client joins after the server has been idle the ball goes off the map
            elapsed = clock.restart();
        }
        
        // Receive data from Client
        // Also receive Client's adress and port from receive function
        sf::Packet data;
        sf::IpAddress adress;
        unsigned short int port;

        m_socket.receive(data, adress, port);

        // Get player data and if the player has left
        float x,y;
        if (data >> x)
        {
            // If error code is sent close server
            if (x == 4.04f)
            {
                m_isRunning = false;
            }
            else
            {
                m_playerPos.x = x;

                if (data >> y)
                {
                    m_playerPos.y = y;
                }
            }
        }
        
        // Send ball data to Client
        data.clear();
        data << m_ballPos.x << m_ballPos.y;

        m_socket.send(data, adress, port);

        // Update ball position
        elapsed = clock.restart();

        m_ballPos.x += m_velocity.x * elapsed.asSeconds() * 100.0f;
        m_ballPos.y += m_velocity.y * elapsed.asSeconds() * 100.0f;

        // Corner hitting
        if (m_ballPos.x < 0 || m_ballPos.x >= 640)
        {
            m_velocity.x *= -1.0f;
        }
        if (m_ballPos.y < 0 || m_ballPos.y >= 480)
        {
            m_velocity.y *= -1.0f;
        }

        // Player hitting ball
        if (m_ballPos.x <= 20 && m_ballPos.y >= m_playerPos.y && m_ballPos.y <= m_playerPos.y + 100.0f)
        {
            m_velocity.x *= -1.0f;
        }
    }

    std::cout << "Closing server!\n";
}