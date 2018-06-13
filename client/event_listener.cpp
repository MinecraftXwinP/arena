#include "event_listener.hpp"
namespace arena {
    template<class ET,class T>
    void event_listener<ET, T>::process(ET event) {
        std::vector<event_handler_func<ET>> handlers = handlerMap[get_event_type(event)];
        for (event_handler_func<ET> *handler : handlers) {
            handler(event);
        }
    }
};
