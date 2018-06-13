#ifndef _H_EVENT_LISTENER_
#define _H_EVENT_LISTENER_

#include <SDL.h>
#include <vector>
#include <map>

namespace arena {
    
    template <class ET>
    using event_handler_func = void(ET);
    
    template <class ET,class T>
    class event_listener {
    public:
        void add_handler(T type, void (*handler) (ET));
        void process(ET);
        virtual T get_event_type(ET event) = 0;
    private:
        std::map<SDL_EventType,std::vector<void(SDL_Event)>> handlerMap;
    };
};

#endif /* event_listener_hpp */
