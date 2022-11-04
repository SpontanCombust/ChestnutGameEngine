#pragma once


#include "chestnut/engine/macros.hpp"
#include "system.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API IRenderingSystem : public ISystem
    {
    public:
        IRenderingSystem( CEngine& engine );
        virtual ~IRenderingSystem() = default;

        virtual void render() = 0;
    };

} // namespace chestnut::engine

