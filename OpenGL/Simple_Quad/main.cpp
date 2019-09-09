#include <gl/glew.h>
#include <SFML/Window.hpp>

#include <stdio.h>

// Raw string literal
const char* vertexShaderSRC = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

const char* fragmentShaderSRC = R"(
    #version 330 core
    out vec4 FragColor;
    
    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    } 
)";


int main()
{
    sf::Window window(sf::VideoMode(640, 480), "GLEW");

    bool bWireFrame = false;

    // Load after window
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Error
        printf("Error: %s\n", glewGetErrorString);
    }
    else printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));

    printf("Press SPACE to enter WireFrame mode\n");

    // On Startup
    ////////////////////////////////////////////////

    // Triangle vertices
    sf::Vector3f vertices[] = {

        {  0.5f,  0.5f, 0.0f },  // top right
        {  0.5f, -0.5f, 0.0f },  // bottom right
        { -0.5f, -0.5f, 0.0f },  // bottom left
        { -0.5f,  0.5f, 0.0f }   // top left 
    };

    // Rectangle Indicies
    unsigned int indicies[] = {
        0, 1, 3,
        1, 2, 3
    };

    // To render something in OPENGL you need atleast a VertexShader and a FragmentShader

    // Create a vertexShader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSRC, NULL);
    glCompileShader(vertexShader);

    // Check for errors in shader source code
    GLint success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR SHADER VERTEX COMPILATION FAILED\n: %s\n", infoLog);
    }

    // Create a fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSRC, NULL);
    glCompileShader(fragmentShader);

    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR SHADER FRAGMENT COMPILATION FAILED\n: %s\n", infoLog);
    }

    // Create the shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    // Combine and link the two shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Compile the program - something like doing make with a makefile
    glLinkProgram(shaderProgram);

    // Check for Program link errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR SHADER PROGRAM COMPILATION FAILED\n: %s\n", infoLog);
    }

    // Clean up memory
    // The shaders have been linked to a program and are useless
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Generate VBO - Vertex Buffer Object
    GLuint VBO;
    // Generate an index for the VBO
    glGenBuffers(1, &VBO);

    // Create VAO - Vertex Array Object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // Create EBO - Element Buffer Object
    // used for telling the gpu how to draw verticies so we don't send duplicate ones
    GLuint EBO;
    glGenBuffers(1, &EBO);

    // Any subsequent vertex attribute calls from that point on will be stored inside the VAO.
    // This has the advantage that when configuring vertex attribute pointers you only have to
    // make those calls once and whenever we want to draw the object,
    // we can just bind the corresponding VAO.   

    // This makes switching between different vertex data and attribute configurations
    // as easy as binding a different VAO. All the state we just set is stored inside the VAO.

    // ..:: Initialization code :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);

    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VBOs
    glBindVertexArray(0);

    ////////////////////////////////////////////////

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;
            if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (bWireFrame)
                {
                    bWireFrame = false;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                else
                {
                    bWireFrame = true;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
            }
        }

        // Clear screen
        // Colours are represented from 0.0f to 1.0f or 0 to 255 in RGB
        glClearColor(0.19f, 0.19f, 0.19f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // On User Update
        ////////////////////////////////////////////////

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Draw first triangle if you remove the EBO
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        ////////////////////////////////////////////////

        window.display();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}