#ifndef _H_SDL_EVENT_LISTENER_
#define _H_SDL_EVENT_LISTENER_
#include <SDL.h>
#include "event_listener.hpp"

namespace arena {
    class sdl_event_listener : public event_listener<SDL_Event,SDL_EventType> {
        virtual SDL_EventType get_event_type(SDL_Event event);
    };
}

#endif
