#ifndef __CHESTNUT_ENGINE_RESOURCE_H__
#define __CHESTNUT_ENGINE_RESOURCE_H__

#include "chestnut/engine/macros.hpp"

// these headers are used by all deriving resource classes
#include <tl/expected.hpp>

#include <memory>


namespace chestnut::engine
{
    class CHESTNUT_API IResource
    {
    public:
        virtual ~IResource() = default;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RESOURCE_H__