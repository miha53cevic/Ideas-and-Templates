#include <GL/glew.h>
#include <SFML/Window.hpp>

#include "Loader.h"
#include "Renderer.h"
#include "Display_Manager.h"

int main()
{
    GLfloat vertices[] = {
        //Bottom Left Triangle
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,

         //Bottom right triangle
          0.5f, -0.5f, 0.0f,
          0.5f,  0.5f, 0.0f,
         -0.5f,  0.5f, 0.0f
    };

    Display_Manager display_manager;
    display_manager.Create({ 640, 480 }, "OpenGL");

    Loader loader;
    Renderer renderer;

    RawModel model = loader.dataToVAO(vertices, sizeof(vertices) / sizeof(vertices[0]));

    while (display_manager.isOpen())
    {
        // window events
        display_manager.checkForClose();

        // Clear
        display_manager.clear();

        renderer.render(model);

        // Display
        display_manager.update();
    }

    return 0;
}