#ifndef _H_EXCEPTION_GL_SHADER_COMPILE_EXCEPTION_
#define _H_EXCEPTION_GL_SHADER_COMPILE_EXCEPTION_
#include "gl_exception.hpp"
namespace arena {
    class gl_shader_compile_exception : public gl_exception {
        public:
            gl_shader_compile_exception(const char* source,const char* log);
        private:
            std::string source;

    };
};
#endif