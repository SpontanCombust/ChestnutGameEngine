#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/types.hpp"

namespace chestnut::engine
{
    struct CHESTNUT_API CRenderLayerComponent
    {
        renderlayer_t layer;

        CRenderLayerComponent();
    };

} // namespace chestnut::engine
