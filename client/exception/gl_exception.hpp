#ifndef _H_EXCEPTION_GL_PROGRAM_EXCEPTION_
#define _H_EXCEPTION_GL_PROGRAM_EXCEPTION_
#include <exception>
#include <string>
namespace arena {
    class gl_exception : public std::exception {
        public:
            gl_exception(std::string log);
            gl_exception();
            gl_exception(const char * log);
            virtual const char* what() const noexcept;
        protected:
            std::string log;
    };
};
#endif