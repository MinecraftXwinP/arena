#include "render_engine.hpp"


namespace arena {
    render_engine::render_engine(SDL_Window* window) {
        this->window = window;
    }
    GLuint compile_shader(GLenum shader_type,const char* source) {
        GLuint shader = glCreateShader(shader_type);
        glShaderSource(shader,1,&source,NULL);
        glCompileShader(shader);
        GLint params;
        glGetShaderiv(shader,GL_COMPILE_STATUS,&params);
        if (params != GL_TRUE) {
            glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&params);
            if (params != 0) {
                char logs[params];
                glGetShaderInfoLog(shader,params,NULL,logs);
                throw gl_shader_compile_exception(source,logs);
            }
            throw gl_exception("cannot compile shader");
        }
        return shader;
    }
    GLuint compile_program(const char *v_shader_path,const char *f_shader_path) {
        std::string v_source = load_file_text(v_shader_path);
        std::string f_source = load_file_text(f_shader_path);
        GLuint v_shader = compile_shader(GL_VERTEX_SHADER, v_source.c_str());         
        GLuint f_shader = compile_shader(GL_FRAGMENT_SHADER, f_source.c_str());
        GLuint program = glCreateProgram();
        glAttachShader(program, v_shader);
        glAttachShader(program, f_shader);
        glLinkProgram(program);
        GLint params;
        glGetProgramiv(program,GL_LINK_STATUS,&params);
        if (params != GL_TRUE) {
            glGetProgramiv(program,GL_INFO_LOG_LENGTH,&params);
            if (params != 0 ) {
                char logs[params];
                glGetProgramInfoLog(program,params,NULL,logs);
                throw gl_exception(std::string("cannot link program:") + logs);
            }
            throw gl_exception("cannot link program");
        }
        glDetachShader(program, v_shader);
        glDetachShader(program,f_shader);
        return program;
    }


    int render_engine::loop() {
        glewExperimental = GL_TRUE;
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,24);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        context = SDL_GL_CreateContext(window);
        glewInit();
        glClearColor(1,1,1,1);
        last_frame_timestamp = SDL_GetTicks();
        GLuint vao,plane;
        try {
            GLuint program = compile_program("shader/plane.vsh","shader/plane.fsh");
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            glGenBuffers(1,&plane);
            glBindBuffer(GL_ARRAY_BUFFER, plane);
            const GLfloat ground[] = {
                -1,1,0,
                -1,-1,0,
                1,1,0,
                1,-1,0
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(ground),ground,GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
            while (running) {
                if (last_frame_timestamp + 1000 <= SDL_GetTicks()) {
                    std::cout << "FPS: " << frame_count << std::endl;
                    frame_count = 0;
                    last_frame_timestamp = SDL_GetTicks();
                }
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glUseProgram(program);
                glBindBuffer(GL_ARRAY_BUFFER,plane);
                glEnableVertexAttribArray(0);
                glDrawArrays(GL_TRIANGLE_STRIP,0,4);
                glDisableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER,0);
                glUseProgram(0);

                SDL_GL_SwapWindow(window);
                frame_count++;
            }
        } catch (const std::exception& e) {
           std::cout << e.what() << std::endl; 
        } catch (...) {
            std::cout << "error" << std::endl;
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
