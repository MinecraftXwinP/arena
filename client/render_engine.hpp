#ifndef _H_RENDER_ENGINE_
#define _H_RENDER_ENGINE_
#include <SDL.h>
#include <iostream>
#include <GL/glew.h>
#include <functional>

namespace arena {
    class render_engine {
        public:
            render_engine(SDL_Window* window);
            void start();
            void destroy();
            static int thread_func(void* data);
        private:
            bool running;
            int loop();
            SDL_Window* window;
            SDL_Thread* thread;
            SDL_GLContext context;
            int last_frame_timestamp;
            int frame_count;
    };
};
#endif