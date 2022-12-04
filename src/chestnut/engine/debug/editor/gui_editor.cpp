#include "chestnut/engine/debug/editor/gui_editor.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_animation2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_collision2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_identity_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_kinematics2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_model2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_render_layer_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_sprite_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_transform2d_component_view.hpp"
#include "chestnut/engine/ecs_impl/factories/component_factory.hpp"

#include <chestnut/ecs/constants.hpp>
#include <imgui.h>

#include <unordered_map>


namespace chestnut::engine::debug
{
    using namespace chestnut::ecs;

    bool s_viewEntityList = true;
    bool s_viewComponentInspector = true;

    bool guiEntityListPanel(entityid_t& selectedEnt)
    {
        static const int ENTITY_NAME_LENGTH = IM_ARRAYSIZE(CIdentityComponent::name);
        static char entityNameInput[ENTITY_NAME_LENGTH] = "";

        bool entityChanged = false;
        auto& world = CEngine::getInstance().getEntityWorld();

        ImGui::SetNextWindowPos({0, 0}, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({200, 600}, ImGuiCond_FirstUseEver);
        if(s_viewEntityList)
        {
            if(ImGui::Begin("Entities", &s_viewEntityList))
            {
                bool confirmedAdd = ImGui::InputText("##createEntity", entityNameInput, ENTITY_NAME_LENGTH, ImGuiInputTextFlags_EnterReturnsTrue);
                ImGui::SameLine();
                if(ImGui::Button("Add") || confirmedAdd)
                {
                    entityid_t id = world.createEntity();
                    auto handle = world.createComponent<CIdentityComponent>(id);
                    strncpy_s(handle->name, entityNameInput, ENTITY_NAME_LENGTH);
                    memset(entityNameInput, 0, ENTITY_NAME_LENGTH);
                }
                
                for(auto it = world.entityIterator.cbegin(); it != world.entityIterator.cend(); it++)
                {
                    std::string entityLabel = "";

                    if(auto handle = world.getComponent<CIdentityComponent>(it.id()))
                    {
                        entityLabel = handle->name;
                    }
                    // happens either if CIdentityComponent was not found or the name field was empty
                    if(entityLabel[0] == '\0')
                    {
                        entityLabel = std::to_string(it.id());
                    }

                    entityLabel += "##" + std::to_string(it.id());

                    if(ImGui::Selectable(entityLabel.c_str(), selectedEnt == it.id()))
                    {
                        if(it.id() != selectedEnt)
                        {
                            entityChanged = true;
                        }

                        selectedEnt = it.id(); 
                    }
                }
            }
        
            ImGui::End();
        }

        return entityChanged;
    }



    struct SComponentData
    {
        const char *name;
        ComponentFactoryCreateCallback factoryCreate;
        ComponentFactoryDisposeCallback factoryDispose;
        IGuiComponentView *guiView;
        bool isPresent;
    };

    // TEMPORARY SOLUTION TO FINDING TYPES!

    static std::unordered_map<std::type_index, SComponentData> mapComponentData = {
        {
            typeid(CAnimation2DComponent),
            { 
                "CAnimation2DComponent",
                CComponentFactory<CAnimation2DComponent>::create,
                CComponentFactory<CAnimation2DComponent>::dispose,
                new CGuiAnimation2DComponentView(),
                false,
            },
        },
        {
            typeid(CCollision2DComponent),
            { 
                "CCollision2DComponent",
                CComponentFactory<CCollision2DComponent>::create,
                CComponentFactory<CCollision2DComponent>::dispose,
                new CGuiCollision2DComponentView(),
                false,
            },
        },
        {
            typeid(CIdentityComponent),
            { 
                "CIdentityComponent",
                CComponentFactory<CIdentityComponent>::create,
                CComponentFactory<CIdentityComponent>::dispose,
                new CGuiIdentityComponentView(),
                false,
            },
        },
        {
            typeid(CKinematics2DComponent),
            { 
                "CKinematics2DComponent",
                CComponentFactory<CKinematics2DComponent>::create,
                CComponentFactory<CKinematics2DComponent>::dispose,
                new CGuiKinematics2DComponentView(),
                false,
            },
        },
        {
            typeid(CModel2DComponent),
            { 
                "CModel2DComponent",
                CComponentFactory<CModel2DComponent>::create,
                CComponentFactory<CModel2DComponent>::dispose,
                new CGuiModel2DComponentView(),
                false,
            },
        },
        {
            typeid(CRenderLayerComponent),
            { 
                "CRenderLayerComponent",
                CComponentFactory<CRenderLayerComponent>::create,
                CComponentFactory<CRenderLayerComponent>::dispose,
                new CGuiRenderLayerComponentView(),
                false,
            },
        },
        {
            typeid(CSpriteComponent),
            { 
                "CSpriteComponent",
                CComponentFactory<CSpriteComponent>::create,
                CComponentFactory<CSpriteComponent>::dispose,
                new CGuiSpriteComponentView(),
                false,
            },
        },
        {
            typeid(CTransform2DComponent),
            { 
                "CTransform2DComponent",
                CComponentFactory<CTransform2DComponent>::create,
                CComponentFactory<CTransform2DComponent>::dispose,
                new CGuiTransform2DComponentView(),
                false,
            },
        },
    };

    void guiComponentInspector(chestnut::ecs::entityid_t entity)
    {
        //TODO if signature changes, reload views

        if(s_viewComponentInspector)
        {
            ImGui::SetNextWindowPos({600, 0}, ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize({200, 600}, ImGuiCond_FirstUseEver);
            if(ImGui::Begin("Inspector", &s_viewComponentInspector))
            {
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

                            // HEADER //
                            ImGui::NewLine();
                            ImGui::SameLine(ImGui::GetWindowWidth() - 20);
                            bool didDelete = ImGui::Button("X##DeleteComponent");
                            
                            // ACTUAL COMPONENT CONTENT//
                            dataIt->second.guiView->fetchComponent(entity);
                            dataIt->second.guiView->drawWidgets();
                            ImGui::NewLine();

                            if(didDelete)
                            {
                                dataIt->second.factoryDispose(entity);
                            }

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
                            data.factoryCreate(entity);
                        }

                        data.isPresent = false;
                    }

                    ImGui::EndPopup();
                }
            }

            ImGui::End();
        }
    }

    void guiMenuBar()
    {
        if(ImGui::BeginMainMenuBar())
        {
            guiMenuBarFile();
            guiMenuBarView();
            
            ImGui::EndMainMenuBar();
        }
    }

    void guiMenuBarFile()
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Save scene..."))
            {

            }

            if(ImGui::MenuItem("Load scene..."))
            {

            }

            ImGui::EndMenu();
        }
    }

    void guiMenuBarView()
    {
        if(ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Entity list", NULL, &s_viewEntityList);
            ImGui::MenuItem("Inspector", NULL, &s_viewComponentInspector);

            ImGui::EndMenu();
        }
    }

} // namespace chestnut::engine::debug
