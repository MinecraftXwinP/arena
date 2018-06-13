#ifndef _H_RENDER_ENGINE_
#define _H_RENDER_ENGINE_
#include <SDL.h>
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <functional>
#include "util/file.hpp"
#include "exception/gl_exception.hpp"
#include "exception/gl_shader_compile_exception.hpp"
#include "camera.hpp"
namespace arena {
    class render_engine {
        public:
            render_engine(int width,int height,SDL_Window* window,camera& camera);
            void start();
            void destroy();
            static int thread_func(void* data);
            void get_size(int size[2]);
            int get_width();
            int get_height();
        private:
            bool running;
            int loop();
            int width;
            int height;
            SDL_Window* window;
            SDL_Thread* thread;
            SDL_GLContext context;
            int last_frame_timestamp;
            int frame_count;
            camera& camera;

    };
};
#endif
