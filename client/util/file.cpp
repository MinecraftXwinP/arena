#include "file.hpp"

namespace arena {
    std::string load_file_text(const char* path) {
        std::FILE* file = fopen(path, "rb");
        if (file == NULL) {
            throw std::runtime_error(strerror(errno));
        }
        fseek(file,0, SEEK_END);
        long length = ftell(file);
        char buffer[length];
        rewind(file);
        fread(buffer,1,length,file);
        fclose(file);
        return buffer;
    }
}

