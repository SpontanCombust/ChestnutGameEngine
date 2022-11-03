#ifndef __CHESTNUT_ENGINE_RENDERING_SYSTEM_H__
#define __CHESTNUT_ENGINE_RENDERING_SYSTEM_H__

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

#endif // __CHESTNUT_ENGINE_RENDERING_SYSTEM_H__