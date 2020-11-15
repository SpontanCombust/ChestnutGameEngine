#ifndef __CHESTNUT_EVENT_BASE_H__
#define __CHESTNUT_EVENT_BASE_H__

#include <string>

namespace chestnut
{
    using event_function = void;

    struct SEvent
    {
        // put here whathever you want in child struct

        virtual const std::string getName() { return "Event"; }
        virtual ~SEvent() {}
    };

} // namespace chestnut


#endif // __CHESTNUT_EVENT_BASE_H__