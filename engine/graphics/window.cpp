#include "window.h"

Window::Window() : window(nullptr), initialized(false), fullscreen(false) {}

Window::~Window()
{
    shutdown();
}

bool Window::initialize(const WindowConfig& config)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return false;
    Uint32 flags = 0;
    window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.width,
                              config.height, flags);
    if (!window)
        return false;
    fullscreen = false;
    initialized = true;
    return true;
}

void Window::shutdown()
{
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    window = nullptr;
    initialized = false;
    fullscreen = false;
}

void Window::toggleFullscreen()
{
    if (!window)
        return;
    fullscreen = !fullscreen;
    SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

SDL_Window* Window::getNativeWindow() const
{
    return window;
}

bool Window::isInitialized() const
{
    return initialized;
}

bool Window::isFullscreen() const
{
    return fullscreen;
}
