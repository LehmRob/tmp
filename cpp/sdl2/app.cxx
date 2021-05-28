#include "app.hxx"

#include <functional>
#include <stdexcept>

#include <SDL.h>

namespace demosdl2 {

App::App(SDL_Window *window) : window(window), running(true) {}

App::~App() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

App App::createApp() {
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Demo SDL2", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        throw std::runtime_error("Can't create SDL window");
    }

    App app(window);

    return app;
}

void App::loop(void) {
    SDL_Event event;
    while (this->running) {
        if (SDL_PollEvent(&event) == 0) {
            continue;
        }

        if (event.type == SDL_WINDOWEVENT) {
            handleWindowEvent(&event);
        }
    }
}

void App::handleWindowEvent(SDL_Event *event) {
    switch (event->window.event) {
    case SDL_WINDOWEVENT_CLOSE:
        quit();
    case SDL_WINDOWEVENT_MOVED:
        std::printf("Window is moved\n");
        break;
    }
}

void App::quit(void) { this->running = false; }

} // namespace demosdl2
