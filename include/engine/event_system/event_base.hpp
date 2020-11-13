#ifndef __CHESTNUT_EVENT_BASE_H__
#define __CHESTNUT_EVENT_BASE_H__

namespace chestnut
{
    typedef void event_function;

    struct SEvent
    {
        // put here whathever you want in child struct

        // provide overriden name for debugging
        virtual const char* getName() { return "SEvent"; }
        virtual ~SEvent() {}
    };

} // namespace chestnut


#endif // __CHESTNUT_EVENT_BASE_H__