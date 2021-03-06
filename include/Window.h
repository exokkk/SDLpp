#pragma once

#ifdef __APPLE__
#ifdef _SDL2
// waf
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#else
#include <SDL2/SDL.h>
#endif

#include <string>
#include <stdint.h>
#include <memory>
#include <set>
#include <functional>
#include "Vector2.h"
#include "Util.h"

namespace sdl {
class Renderer;
class Window {
private:
    typedef std::unique_ptr<Renderer> renderer_ptr;
    SDL_Window *_win;
    std::set<renderer_ptr> _renderers;
public:
    Window(const std::string name)
        : Window(name, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP) {}

    Window(const std::string name, const int width, const int height)
        : Window(name, width, height, SDL_WINDOW_SHOWN) {}

    Window(const std::string name,
           const uint32_t flags)
        : Window(name, 0, 0, flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {}

    Window(const std::string name,
           const int width,
           const int height,
           const uint32_t flags)
        : _win(nullptr) {
        _win = SDL_CreateWindow(name.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                width, height,
                                flags);
        if (_win == nullptr) {
            printf("Could not create window: %s\n", SDL_GetError());
            Throw();
        }
    }

    Window(Window&& other) {
        _win = other._win;
        _renderers = std::move(other._renderers);

        other._win = nullptr;
        other._renderers.clear();
    }

    Window(const Window &other) = delete;
    Window &operator=(const Window &other) = delete;

    ~Window() {
        if (_win != nullptr) SDL_DestroyWindow(_win);
    }

    Vector2i GetSize() const;

    void GrabInput() { SDL_SetWindowGrab(_win, SDL_TRUE); }
    void ReleaseInput() { SDL_SetWindowGrab(_win, SDL_FALSE); }

    Renderer *CreateRenderer();
    Renderer *CreateRenderer(const uint32_t flags);
};
}
