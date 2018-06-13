#ifndef _H_IMMERSIVE_CONTROLLER_
#define _H_IMMERSIVE_CONTROLLER_
#include "camera_controller.hpp"
namespace arena {
    class immersive_controller : public camera_controller {
        public:
            immersive_controller(int width, int height,class camera& camera);
            virtual void handleEvent(SDL_Event event);
    };
};

#endif
