#ifndef __CHESTNUT_ENGINE_DYNAMIC_TEXTURE2D_H__
#define __CHESTNUT_ENGINE_DYNAMIC_TEXTURE2D_H__

#include "texture2d.hpp"
#include "../resources/dynamic_texture2d_resource.hpp"

namespace chestnut::engine
{
    class CDynamicTexture2D : public CTexture2D
    {
    public:
        CDynamicTexture2D() = default;
        explicit CDynamicTexture2D( std::shared_ptr< CDynamicTexture2DResource > resource );

        const std::shared_ptr<CDynamicTexture2DResource> getResourceDynamic() const;

        void setAsRenderTarget();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_DYNAMIC_TEXTURE2D_H__