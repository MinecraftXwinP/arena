#include "render_engine.hpp"


namespace arena {
    render_engine::render_engine(SDL_Window* window) {
        this->window = window;
    }

    int render_engine::loop() {
        glewExperimental = GL_TRUE;
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        context = SDL_GL_CreateContext(window);
        glewInit();
        glClearColor(1,1,1,1);
        last_frame_timestamp = SDL_GetTicks();
        while (running) {
            if (last_frame_timestamp + 1000 <= SDL_GetTicks()) {
                std::cout << "FPS: " << frame_count << std::endl;
                frame_count = 0;
                last_frame_timestamp = SDL_GetTicks();
            }
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window);
            frame_count++;
        }
        SDL_GL_DeleteContext(context);
        return 0;
    }
    int render_engine::thread_func(void *data) {
        return ((render_engine*)data)->loop();
    }


    void render_engine::start() {
        running = true;
        thread = SDL_CreateThread(thread_func,"rendering",this);
    }

    void render_engine::destroy() {
        running = false;
        
    }
}