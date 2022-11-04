#pragma once


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

