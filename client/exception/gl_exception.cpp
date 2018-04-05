#include "gl_exception.hpp"

namespace arena {
    gl_exception::gl_exception(std::string log) : std::exception() {
        this->log = log;
    }
    gl_exception::gl_exception(const char* log) : std::exception() {
        this->log = log;
    }
    gl_exception::gl_exception() : std::exception() {}
    const char* gl_exception::what() const noexcept {
        return this->log.c_str();
    }
};