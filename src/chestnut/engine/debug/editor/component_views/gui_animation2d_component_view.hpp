#pragma once


#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
#include "chestnut/engine/ecs_impl/components/animation2d_component.hpp"

#include <chestnut/ecs/component_handle.hpp>

#include <vector>


namespace chestnut::engine::debug
{
    class CGuiAnimation2DComponentView : public IGuiComponentView
    {
    private:
        ecs::CComponentHandle<CAnimation2DComponent> m_handle;

        std::string m_animResourcePath;
        int m_selectedAnimIdx = -1;
        std::vector<const char *> m_cachedAnimNames;

    public:
        CGuiAnimation2DComponentView() noexcept;

        void fetchComponent(ecs::entityid_t entity) override;
        void drawWidgets() override;
    };

} // namespace chestnut::engine::debug
