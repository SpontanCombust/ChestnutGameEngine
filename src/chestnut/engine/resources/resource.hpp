#ifndef __CHESTNUT_ENGINE_RESOURCE_H__
#define __CHESTNUT_ENGINE_RESOURCE_H__

// these headers are used by all deriving resource classes
#include <tl/expected.hpp>

#include <memory>


namespace chestnut::engine
{
    class IResource
    {
    public:
        virtual ~IResource() = default;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RESOURCE_H__