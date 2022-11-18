#pragma once


#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
#include "chestnut/engine/ecs_impl/components/sprite_component.hpp"

#include <chestnut/ecs/component_handle.hpp>


namespace chestnut::engine::debug
{
    class CGuiSpriteComponentView : public IGuiComponentView
    {
    private:
        ecs::CComponentHandle<CSpriteComponent> m_handle;

        std::string m_texturePath;
        SRectangle m_clippingRect;
        vec3f m_tint;
        float m_tintFactor;
        int m_selectedAdjustToModel;

    public:
        void fetchComponent(ecs::entityid_t entity) override;
        void drawWidgets() override;
    };

} // namespace chestnut::engine::debug
