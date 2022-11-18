#include "chestnut/engine/debug/editor/gui_editor.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_animation2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_collision2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_kinematics2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_model2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_render_layer_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_sprite_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_transform2d_component_view.hpp"
#include "chestnut/engine/ecs_impl/factories/component_factories.hpp"

#include <chestnut/ecs/constants.hpp>
#include <imgui.h>

#include <unordered_map>


namespace chestnut::engine::debug
{
    using namespace chestnut::ecs;

    bool guiEntityListPanel(entityid_t& selectedEnt)
    {
        static char entityNameInput[65] = "";

        bool entityChanged = false;
        auto& world = CEngine::getInstance().getEntityWorld();

        ImGui::SetNextWindowPos({0, 0}, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({200, 600}, ImGuiCond_FirstUseEver);
        ImGui::Begin("Entity list");

        //TODO CNameComponent or something...
        ImGui::InputText("##createEntity", entityNameInput, IM_ARRAYSIZE(entityNameInput));
        ImGui::SameLine();
        if(ImGui::Button("Add"))
        {
            world.createEntity();
            entityNameInput[0] = '\0';
        }
        
        for(auto it = world.entityIterator.cbegin(); it != world.entityIterator.cend(); it++)
        {
            char entityLabelBuff[11];
            snprintf(entityLabelBuff, IM_ARRAYSIZE(entityLabelBuff), "%d", it.id());
            if(ImGui::Selectable(entityLabelBuff, selectedEnt == it.id()))
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



    struct SComponentData
    {
        const char *name;
        bool (*factory)(ecs::entityid_t);
        IGuiComponentView *guiView;
        bool isPresent;
    };

    // TEMPORARY SOLUTION TO FINDING TYPES!

    static std::unordered_map<std::type_index, SComponentData> mapComponentData = {
        {
            typeid(CCollision2DComponent),
            { 
                "CCollision2DComponent",
                componentFactory_CCollision2DComponent,
                new CGuiCollision2DComponentView(),
                false,
            },
        },
        {
            typeid(CKinematics2DComponent),
            { 
                "CKinematics2DComponent",
                componentFactory_CKinematics2DComponent,
                new CGuiKinematics2DComponentView(),
                false,
            },
        },
        {
            typeid(CModel2DComponent),
            { 
                "CModel2DComponent",
                componentFactory_CModel2DComponent,
                new CGuiModel2DComponentView(),
                false,
            },
        },
        {
            typeid(CRenderLayerComponent),
            { 
                "CRenderLayerComponent",
                componentFactory_CRenderLayerComponent,
                new CGuiRenderLayerComponentView(),
                false,
            },
        },
        {
            typeid(CSpriteComponent),
            { 
                "CSpriteComponent",
                componentFactory_CSpriteComponent,
                new CGuiSpriteComponentView(),
                false,
            },
        },
        {
            typeid(CTransform2DComponent),
            { 
                "CTransform2DComponent",
                componentFactory_CTransform2DComponent,
                new CGuiTransform2DComponentView(),
                false,
            },
        },
    };

    void guiComponentListPanel(chestnut::ecs::entityid_t entity)
    {
        ImGui::SetNextWindowPos({600, 0}, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({200, 600}, ImGuiCond_FirstUseEver);
        ImGui::Begin("Component list");
            const auto& world = CEngine::getInstance().getEntityWorld();
            auto sign = world.getEntitySignature(entity);

            for(const auto& type: sign.m_setComponentTypes)
            {
                auto dataIt = mapComponentData.find(type);
                if(dataIt != mapComponentData.end())
                {
                    if(ImGui::CollapsingHeader(dataIt->second.name, ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        ImGui::PushID(dataIt->second.name);
                        dataIt->second.guiView->fetchComponent(entity);
                        dataIt->second.guiView->drawWidgets();
                        ImGui::NewLine();
                        ImGui::PopID();
                    }
                    ImGui::Separator();

                    dataIt->second.isPresent = true;
                }
            }

            if(ImGui::Button("Add...", {-1, 0}))
            {
                ImGui::OpenPopup("AddComponentPopup");
            }

            if(ImGui::BeginPopup("AddComponentPopup"))
            {
                for (auto& [_, data] : mapComponentData)
                {
                    if(!data.isPresent && ImGui::Selectable(data.name))
                    {
                        data.factory(entity);
                    }

                    data.isPresent = false;
                }

                ImGui::EndPopup();
            }
        ImGui::End();
    }

} // namespace chestnut::engine::debug
