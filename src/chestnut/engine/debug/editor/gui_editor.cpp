#include "chestnut/engine/debug/editor/gui_editor.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/component_rtti.hpp"
#include "chestnut/engine/ecs_impl/components/identity_component.hpp"
#include "chestnut/engine/resources/scene_resource.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"

#include <chestnut/ecs/constants.hpp>
#include <imgui.h>
#include <nfd.h>

#include <unordered_map>


namespace chestnut::engine::debug
{
    using namespace chestnut::ecs;

    bool s_viewEntityList = true;
    bool s_viewComponentInspector = true;

    //TODO entity deletion
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

                    if(ImGui::BeginPopupContextItem())
                    {
                        if(ImGui::Button("Remove"))
                        {
                            world.destroyEntity(selectedEnt);
                        }

                        ImGui::EndPopup();
                    }
                }
            }
        
            ImGui::End();
        }

        return entityChanged;
    }





    void guiComponentInspector(chestnut::ecs::entityid_t entity)
    {
        auto rtti = getComponentRTTIRegistry();

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
                    auto traitsIt = rtti.find(type);
                    if(traitsIt != rtti.end())
                    {
                        if(ImGui::CollapsingHeader(traitsIt->second.name, ImGuiTreeNodeFlags_DefaultOpen))
                        {
                            ImGui::PushID(traitsIt->second.name);

                            // HEADER //
                            ImGui::NewLine();
                            ImGui::SameLine(ImGui::GetWindowWidth() - 20);
                            bool didDelete = ImGui::Button("X##DeleteComponent");
                            
                            // ACTUAL COMPONENT CONTENT//
                            if(traitsIt->second.guiView)
                            {
                                traitsIt->second.guiView->fetchComponent(entity);
                                traitsIt->second.guiView->drawWidgets();
                            }
                            ImGui::NewLine();

                            if(didDelete)
                            {
                                traitsIt->second.factoryDispose(entity);
                            }

                            ImGui::PopID();
                        }

                        ImGui::Separator();
                    }
                }

                if(ImGui::Button("Add...", {-1, 0}))
                {
                    ImGui::OpenPopup("AddComponentPopup");
                }

                if(ImGui::BeginPopup("AddComponentPopup"))
                {
                    for (auto& [typeIndex, traits] : rtti)
                    {
                        if(!sign.has(typeIndex) && ImGui::Selectable(traits.name))
                        {
                            traits.factoryCreate(entity);
                        }
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
                static const std::string errBeginning("Error occured when saving the scene to file:\n");

                nfdchar_t *filePath = NULL;
                nfdresult_t result = NFD_SaveDialog(
                    makeNFDFiltersList(CSceneResource::SUPPORTED_FILE_EXTENSIONS).c_str(), 
                    std::filesystem::absolute(CHESTNUT_ENGINE_ASSETS_DIR_PATH).string().c_str(), 
                    &filePath 
                );

                if(result == NFD_OKAY) 
                {
                    auto resource = CSceneResource::loadFromEntityWorld();
                    if(resource)
                    {
                        (**resource).saveToFile(filePath).map([](const std::string& err) {
                            LOG_ERROR(err);
                            messageBoxInfo(errBeginning + err);
                        });
                    }
                    else
                    {
                        LOG_ERROR(resource.error());
                        messageBoxInfo(errBeginning + resource.error());
                    }

                    NFD_Free(filePath);
                }
                else if(result == NFD_ERROR)
                {
                    LOG_ERROR(NFD_GetError());
                    messageBoxInfo(errBeginning + NFD_GetError());
                }
            }


            if(ImGui::MenuItem("Load scene..."))
            {
                static const std::string errBeginning("Error occured when saving the scene to file:\n");

                nfdchar_t *filePath = NULL;
                nfdresult_t result = NFD_OpenDialog( 
                    makeNFDFiltersList(CSceneResource::SUPPORTED_FILE_EXTENSIONS).c_str(), 
                    std::filesystem::absolute(CHESTNUT_ENGINE_ASSETS_DIR_PATH).string().c_str(), 
                    &filePath 
                );

                if(result == NFD_OKAY) 
                {
                    auto resource = CSceneResource::loadFromFile(filePath);
                    if(resource)
                    {
                        if(auto err = (**resource).parseAndTransferToScene())
                        {
                            LOG_ERROR(err.value());
                            messageBoxInfo(errBeginning + err.value());
                        }
                    }
                    else
                    {
                        LOG_ERROR(resource.error());
                        messageBoxInfo(errBeginning + resource.error());
                    }
                    
                    NFD_Free(filePath);
                }
                else if(result == NFD_ERROR)
                {
                    LOG_ERROR(NFD_GetError());
                    messageBoxInfo(errBeginning + NFD_GetError());
                }
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
