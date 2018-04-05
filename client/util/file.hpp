#ifndef _H_UTIL_FILE_
#define _H_UTIL_FILE_
#include <cstdio>
#include <cerrno>
#include <exception>
#include <string>

namespace arena {
    std::string load_file_text(const char* path);
};

#endif