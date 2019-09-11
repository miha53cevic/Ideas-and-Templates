#include "Display_Manager.h"

#include <GL/glew.h>
#include <iostream>

Display_Manager::Display_Manager()
{
}

void Display_Manager::Create(sf::Vector2u size, std::string title)
{
    m_window = std::make_unique<sf::Window>(sf::VideoMode(size.x, size.y), title);
    m_isRunning = true;

    // Load after window
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Error
        printf("Error: %s\n", glewGetErrorString);
    }
    else std::cout << "Using GLEW" << glewGetString(GLEW_VERSION) << "\n";

    m_window->setActive(true);
}

void Display_Manager::checkForClose()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_isRunning = false;
        if (event.type == sf::Event::Resized)
            glViewport(0, 0, event.size.width, event.size.height);
    }
}

bool Display_Manager::isOpen()
{
    return m_isRunning;
}

void Display_Manager::update()
{
    m_window->display();
}

void Display_Manager::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
