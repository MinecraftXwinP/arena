#ifndef _H_CAMERA_CONTROLLER_
#define _H_CAMERA_CONTROLLER_
#include "camera.hpp"
#include <SDL.h>
namespace arena {
    class camera_controller {
    public:
        camera_controller(int width,int height,camera& camera);
        virtual void handleEvent(SDL_Event event);
        void set_lock(bool lock);
    protected:
        int width;
        int height;
        camera& camera;
        bool lock;
    };
};

#endif
