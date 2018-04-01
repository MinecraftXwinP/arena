#include <SDL.h>
#include "render_engine.hpp"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *w = SDL_CreateWindow(
        "Areana",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,640,
        SDL_WINDOW_OPENGL
    );
    bool running = true;
    arena::render_engine render_engine(w);
    render_engine.start();
    while (running) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    render_engine.destroy();
                    SDL_DestroyWindow(w);
                    break;
            }
        }
    }
    SDL_Quit();
}