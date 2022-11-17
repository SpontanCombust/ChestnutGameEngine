#include "chestnut/engine/debug/editor/gui_editor.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_animation2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_collision2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_model2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_sprite_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_transform2d_component_view.hpp"

#include <chestnut/ecs/constants.hpp>
#include <imgui.h>

#include <unordered_map>


namespace chestnut::engine::debug
{
    using namespace chestnut::ecs;

    bool guiEntityListPanel(entityid_t& selectedEnt)
    {
        bool entityChanged = false;

        ImGui::SetNextWindowPos({0, 0}, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({200, 600}, ImGuiCond_FirstUseEver);
        ImGui::Begin("Entity list");

        const auto& world = CEngine::getInstance().getEntityWorld();
        for(auto it = world.entityIterator.cbegin(); it != world.entityIterator.cend(); it++)
        {
            char buff[11];
            snprintf(buff, IM_ARRAYSIZE(buff), "%d", it.id());
            if(ImGui::Selectable(buff, selectedEnt == it.id()))
            {
                if(it.id() != selectedEnt)
                {
                    entityChanged = true;
                }

                selectedEnt = it.id(); 
            }
        }
        
        ImGui::End();

        return entityChanged;
    }



    void guiComponentListPanel(chestnut::ecs::entityid_t entity)
    {
        static std::unordered_map<std::type_index, IGuiComponentView *> editPanels = {
            {typeid(CTransform2DComponent), new CGuiTransform2DComponentView()},
            {typeid(CSpriteComponent), new CGuiSpriteComponentView()},
            {typeid(CModel2DComponent), new CGuiModel2DComponentView()}
        };

        ImGui::SetNextWindowPos({600, 0}, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({200, 600}, ImGuiCond_FirstUseEver);
        ImGui::Begin("Component list");
            const auto& world = CEngine::getInstance().getEntityWorld();
            auto sign = world.getEntitySignature(entity);

            for(const auto& type: sign.m_setComponentTypes)
            {
                auto ep = editPanels[type];
                if(ep != nullptr)
                {
                    ep->fetchComponent(entity);
                    ep->drawGuiWindow();
                }
            }
        ImGui::End();
    }

} // namespace chestnut::engine::debug
