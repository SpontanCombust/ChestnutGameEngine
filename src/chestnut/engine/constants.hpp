#pragma once


#include "types.hpp"

#include <limits>

namespace chestnut::engine
{
    constexpr double CHESTNUT_PI = 3.14159265359;


    const listenerpriority_t LISTENER_PRIORITY_HIGHEST = std::numeric_limits<listenerpriority_t>::min();

    const listenerpriority_t LISTENER_PRIORITY_LOWEST = std::numeric_limits<listenerpriority_t>::max();

    const listenerpriority_t LISTENER_PRIORITY_ANY = LISTENER_PRIORITY_LOWEST;


    const systempriority_t SYSTEM_PRIORITY_HIGHEST = 0;

    const systempriority_t SYSTEM_PRIORITY_LOWEST = std::numeric_limits<systempriority_t>::max();

    const systempriority_t SYSTEM_PRIORITY_ANY = SYSTEM_PRIORITY_LOWEST;

    const systempriority_t SYSTEM_PRIORITY_INVALID = -1;


    const renderlayer_t RENDER_LAYER_HIGHEST = std::numeric_limits<renderlayer_t>::max();

    const renderlayer_t RENDER_LAYER_LOWEST = std::numeric_limits<renderlayer_t>::min();

    const renderlayer_t RENDER_LAYER_DEFAULT = 0;

} // namespace chestnut::engine

