#include "sdl_event_listener.hpp"
namespace arena {
    SDL_EventType sdl_event_listener::get_event_type(SDL_Event event)  {
        return (SDL_EventType)event.type;
    }
};
