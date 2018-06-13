#include "render_engine.hpp"


namespace arena {
    const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };
    render_engine::render_engine(int width,int height,SDL_Window* window,class camera& camera) :
        width(width),height(height),window(window), camera(camera){}
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
//        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        context = SDL_GL_CreateContext(window);
        glewInit();
        glClearColor(1,1,1,1);
        last_frame_timestamp = SDL_GetTicks();
        GLuint vao;
        GLuint buffers[2];
        try {
            GLuint program = compile_program("shader/plane.vsh","shader/plane.fsh");
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            glGenBuffers(2,buffers);
            
            const GLfloat ground[] = {
                -1,1,0,
                -1,-1,0,
                1,1,0,
                1,-1,0
            };
            
            glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
            
            glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(g_color_buffer_data),g_color_buffer_data,GL_STATIC_DRAW);
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
            
            glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(0.8,0.8,0.8));

            glm::mat4 project = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

            GLuint mvp_location = glGetUniformLocation(program,"mvp");

            while (running) {
                if (last_frame_timestamp + 1000 <= SDL_GetTicks()) {
                    std::cout << "FPS: " << frame_count << std::endl;
                    frame_count = 0;
                    last_frame_timestamp = SDL_GetTicks();
                }
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glUseProgram(program);
                glm::mat4 view = camera.get_view_matrix();
                glm::mat4 mvp = project * view * model;
                glUniformMatrix4fv(mvp_location,1,GL_FALSE,&mvp[0][0]);
                glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
                glEnableVertexAttribArray(1);
                glDrawArrays(GL_TRIANGLES,0,36);
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
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
    
    void render_engine::get_size(int size[2]) {
        SDL_GetWindowSize(window, &size[0],&size[1]);
    }
    
    int render_engine::get_width() {
        int size[2];
        get_size(size);
        return size[0];
    }
    
    int render_engine::get_height() {
        int size[2];
        get_size(size);
        return size[1];
    }
}
