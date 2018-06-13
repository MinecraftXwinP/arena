#include "immersive_controller.hpp"

namespace arena {
    
    immersive_controller::immersive_controller(int width, int height,class camera& camera) : camera_controller(width,height,camera) {}
    
    void immersive_controller::handleEvent(SDL_Event event) {
        SDL_Window *window = SDL_GetWindowFromID(event.motion.windowID);
        SDL_WarpMouseInWindow(window, width / 2, height / 2);
        camera_controller::handleEvent(event);
    }
}
