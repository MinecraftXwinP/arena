#ifndef _H_CAMERA_
#define _H_CAMERA_
#include <glm/gtc/matrix_transform.hpp>
namespace arena {
    class camera {
    public:
        camera();
        void look_at(glm::vec3 location);
        glm::mat4 get_view_matrix();
    private:
        glm::vec3 looking_at;
    };
};
#endif
