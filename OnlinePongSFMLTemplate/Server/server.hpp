#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Server
{
public:
    Server();
    ~Server();

    void run();

private:
    sf::UdpSocket m_socket;

    sf::Vector2f m_ballPos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_playerPos;

    uint8_t m_Score;

    bool m_isRunning;

    sf::Clock clock;
    sf::Time elapsed;
};