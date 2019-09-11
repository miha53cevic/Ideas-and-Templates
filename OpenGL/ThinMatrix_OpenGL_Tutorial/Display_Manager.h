#pragma once
#include <SFML/Window.hpp>
#include <string>

class Display_Manager
{
public:
    Display_Manager();

    void Create(sf::Vector2u size, std::string title);
    void checkForClose();
    bool isOpen();
    void update();
    void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);

private:
    std::unique_ptr<sf::Window> m_window;
    bool m_isRunning;
};

