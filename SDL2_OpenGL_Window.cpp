#ifdef __linux__
    #include <SDL2/SDL.h>
#elif _WIN32
    #include <SDL.h>
#endif

#include <glad/glad.h>

#include <cstdio>

void SDL_die(const char* message)
{
    printf("%s: %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(2);
}

static SDL_Window* window = nullptr;
static SDL_GLContext maincontext;
static const int ScreenWidth = 640;
static const int ScreenHeight = 480;

void init_window(const char* title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_die("Couldn't initialize SDL_VIDEO");
    
    // Let SDL load the standard OpenGL of the system
    SDL_GL_LoadLibrary(nullptr);

    // Request an OpenGL 3.3 context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request a depth buffer for later
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create the window
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        ScreenWidth, ScreenHeight, SDL_WINDOW_OPENGL
    );

    // Create maincontext
    maincontext = SDL_GL_CreateContext(window);
    if (maincontext == nullptr)
        SDL_die("Failed to create OpenGL context");

    // Check OpenGL properties
    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Set V-Sync
    SDL_GL_SetSwapInterval(1);
}

int main(int argc, char* argv[])
{
    init_window("OpenGL Window");
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        glViewport(0, 0, ScreenWidth, ScreenHeight);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Display
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}