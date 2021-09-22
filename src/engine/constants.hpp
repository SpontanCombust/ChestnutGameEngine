#ifndef __CHESTNUT_CONSTANTS_H__
#define __CHESTNUT_CONSTANTS_H__

#include "types.hpp"

#include <limits>

namespace chestnut
{
    const double CHESTNUT_PI = 3.14159265359;

    const listenerpriority_t LISTENER_PRIORITY_HIGHEST = std::numeric_limits<listenerpriority_t>::min();

    const listenerpriority_t LISTENER_PRIORITY_LOWEST = std::numeric_limits<listenerpriority_t>::max();

    const listenerpriority_t LISTENER_PRIORITY_ANY = LISTENER_PRIORITY_LOWEST;

} // namespace chestnut


#endif // __CHESTNUT_CONSTANTS_H__