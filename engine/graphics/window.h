#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

struct WindowConfig
{
    std::string title;
    int width;
    int height;
    bool fullscreen;
};

class IWindow
{
  public:
    virtual ~IWindow() = default;
    virtual bool initialize(const WindowConfig& config) = 0;
    virtual void shutdown() = 0;
    virtual void toggleFullscreen() = 0;
    virtual SDL_Window* getNativeWindow() const = 0;
    virtual bool isInitialized() const = 0;
    virtual bool isFullscreen() const = 0;
};

class Window : public IWindow
{
  public:
    Window();
    ~Window();
    bool initialize(const WindowConfig& config) override;
    void shutdown() override;
    void toggleFullscreen() override;
    SDL_Window* getNativeWindow() const override;
    bool isInitialized() const override;
    bool isFullscreen() const override;

  private:
    SDL_Window* window;
    bool initialized;
    bool fullscreen;
};

#endif
