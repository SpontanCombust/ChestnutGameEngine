#ifndef __CHESTNUT_ENGINE_RESOURCE_H__
#define __CHESTNUT_ENGINE_RESOURCE_H__

#include <cstddef>


namespace chestnut::engine
{
    class IResource
    {
    public:
        virtual ~IResource() = default;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RESOURCE_H__