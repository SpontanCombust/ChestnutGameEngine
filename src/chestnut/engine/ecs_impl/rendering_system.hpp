#ifndef __CHESTNUT_ENGINE_RENDERING_SYSTEM_H__
#define __CHESTNUT_ENGINE_RENDERING_SYSTEM_H__

#include "system.hpp"

namespace chestnut
{
    class IRenderingSystem : public ISystem
    {
    public:
        IRenderingSystem( CEngine& engine );
        virtual ~IRenderingSystem() = default;

        virtual void render() = 0;
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_RENDERING_SYSTEM_H__