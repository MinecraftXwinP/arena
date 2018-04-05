#include "gl_shader_compile_exception.hpp"

namespace arena {
    gl_shader_compile_exception::gl_shader_compile_exception(const char * source,const char *log) : gl_exception() {
        this->log = std::string("error_log: ").append(log).append(" source:\"").append(source).append("\"");
    }
};