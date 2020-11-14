#ifndef __CHESTNUT_EVENT_BASE_H__
#define __CHESTNUT_EVENT_BASE_H__

#include <functional>

namespace chestnut
{
    using event_function = void;

    struct SEvent
    {
        // put here whathever you want in child struct

        // provide overriden name for debugging
        virtual const char* getName() { return "SEvent"; }
        virtual ~SEvent() {}
    };

} // namespace chestnut


#endif // __CHESTNUT_EVENT_BASE_H__