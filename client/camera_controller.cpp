#include "camera_controller.hpp"


namespace arena {
    camera_controller::camera_controller(int width, int height,class camera& camera) : width(width),height(height),camera(camera),lock(false) {}
    
    void camera_controller::handleEvent(SDL_Event event) {
        if (lock) {
            return;
        }
        float w = (float)event.motion.x / width;
        float h = (float)event.motion.y / height;
        camera.look_at(glm::vec3(w,h,0));
    }
    
    void camera_controller::set_lock(bool lock) {
        this->lock = lock;
    }
};
