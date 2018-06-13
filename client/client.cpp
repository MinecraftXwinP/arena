#include <SDL.h>
#include "render_engine.hpp"
#include "camera_controller.hpp"
#include "immersive_controller.hpp"

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
    arena::camera camera;
    arena::camera_controller camera_controller(800,640,camera);
//    camera_controller.set_lock(true);
    arena::render_engine render_engine(800,640,w,camera);

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
            camera_controller.handleEvent(event);
        }
    }
    SDL_Quit();
}
