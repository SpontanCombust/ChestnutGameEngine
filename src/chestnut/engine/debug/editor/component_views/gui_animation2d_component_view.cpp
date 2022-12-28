#include "chestnut/engine/debug/editor/component_views/gui_animation2d_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/resources/animation2d_resource.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"

#include <nfd.h>


namespace chestnut::engine::debug
{
    CGuiAnimation2DComponentView::CGuiAnimation2DComponentView() noexcept
    {
        m_animResourcePath.reserve(128);
    }

    void CGuiAnimation2DComponentView::fetchComponent(ecs::entityid_t entity) 
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CAnimation2DComponent>(entity);

        m_cachedAnimNames.clear();
        if(m_handle->animationResource)
        {
            m_animResourcePath = m_handle->animationResource->m_location.value_or("").string();

            for(const auto& [animName, _] : m_handle->animationResource->m_animationSet.mapAnimNameToAnimData)
            {
                m_cachedAnimNames.push_back(animName.c_str());
            }
        }
        else
        {
            m_animResourcePath = "";
        }
    }

    void CGuiAnimation2DComponentView::drawWidgets() 
    {
        ImGui::Text("Animation resource path");
        ImGui::InputText(
            "##Animation resource path", 
            (char *)m_animResourcePath.c_str(),
            m_animResourcePath.capacity() + 1, 
            ImGuiInputTextFlags_ReadOnly);
        ImGui::SameLine();
        if(ImGui::Button("...##browseForAnimationResource"))
        {
            nfdchar_t *filePath = NULL;
            nfdresult_t result = NFD_OpenDialog(
                makeNFDFiltersList(CAnimation2DResource::SUPPORTED_FILE_EXTENSIONS).c_str(), 
                std::filesystem::absolute(CHESTNUT_ENGINE_ASSETS_DIR_PATH).string().c_str(), 
                &filePath 
            );
            
            static const std::string errBeginning("Error occured when loading animation file:\n");

            if(result == NFD_OKAY) 
            {
                auto loaded = CEngine::getInstance()
                    .getResourceManager()
                    .getOrLoadResource<CAnimation2DResource>(filePath);

                if(loaded.has_value())
                {
                    m_handle->animationResource = loaded.value();

                    if(m_handle->animationResource->m_animationSet.mapAnimNameToAnimData.size() > 0)
                    {
                        m_selectedAnimIdx = 0;
                    }
                }
                else
                {
                    LOG_ERROR(loaded.error());
                    messageBoxInfo(errBeginning + loaded.error());
                }

                NFD_Free(filePath);
            }
            else if(result == NFD_ERROR)
            {
                messageBoxInfo(errBeginning + NFD_GetError());
            }
        }
        
        ImGui::NewLine();

        ImGui::BeginDisabled(m_handle->isAnimPlaying);

            ImGui::Text("Animation name");
            ImGui::Combo(
                "##Animation name",
                &m_selectedAnimIdx,
                m_cachedAnimNames.data(),
                m_cachedAnimNames.size());
            
            ImGui::Text("Loops");
            ImGui::DragInt("##Loops", &m_handle->remainingAnimLoops);

            ImGui::Text("Speed multiplier");
            ImGui::DragFloat("##Speed multiplier", &m_handle->animSpeedMultiplier, 0.01f);

        ImGui::EndDisabled();

        if(!m_handle->isAnimPlaying)
        {
            if(ImGui::Button("Play"))
            {
                if(m_selectedAnimIdx >= 0)
                {
                    m_handle->playAnimation(m_cachedAnimNames[m_selectedAnimIdx]);
                }
                else
                {
                    LOG_ERROR("Unable to play animation. The name is invalid.")
                    m_selectedAnimIdx = -1;
                }
            }
        }
        else
        {
            const char *resumeOrPause = m_handle->isAnimPaused ? "Resume" : "Pause";

            if(ImGui::Button(resumeOrPause))
            {
                m_handle->isAnimPaused = !m_handle->isAnimPaused;
            }
        }

        ImGui::SameLine();

        if(ImGui::Button("Stop"))
        {
            m_handle->stopAnimation();
        }
    }

} // namespace chestnut::engine
