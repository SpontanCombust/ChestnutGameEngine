#ifndef __CHESTNUT_ENGINE_RENDER_LAYER_COMPONENT_H__
#define __CHESTNUT_ENGINE_RENDER_LAYER_COMPONENT_H__

#include "chestnut/engine/macros.hpp"
#include "../../types.hpp"

namespace chestnut::engine
{
    struct CHESTNUT_API CRenderLayerComponent
    {
        renderlayer_t layer;

        CRenderLayerComponent();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RENDER_LAYER_COMPONENT_H__