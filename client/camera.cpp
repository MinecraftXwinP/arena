#include "camera.hpp"
namespace arena {
    camera::camera() : looking_at(0,0,0) {}
    void camera::look_at(glm::vec3 location) {
        looking_at = location;
    }
    glm::mat4 camera::get_view_matrix() {
        return glm::lookAt(glm::vec3(4,3,3), looking_at, glm::vec3(0,1,0));
    }
};
