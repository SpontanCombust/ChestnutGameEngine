#ifndef __CHESTNUT_ENGINE_TYPES_H__
#define __CHESTNUT_ENGINE_TYPES_H__

#include <cstdint>
#include <typeindex>

namespace chestnut::engine
{    
    typedef void event_function;

    typedef unsigned int timerid_t;

    typedef unsigned short listenerpriority_t;

    typedef signed short systempriority_t;

    typedef int audiochannel_t;

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TYPES_H__