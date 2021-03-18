#ifndef __CHESTNUT_QUIT_REQUEST_EVENT_H__
#define __CHESTNUT_QUIT_REQUEST_EVENT_H__

#include "../event_base.hpp"

namespace chestnut
{
    struct SQuitRequestEvent : SEvent
    {
        const std::string getName() { return "QuitRequestEvent"; }
    };
    
} // namespace chestnut


#endif // __CHESTNUT_QUIT_REQUEST_EVENT_H__