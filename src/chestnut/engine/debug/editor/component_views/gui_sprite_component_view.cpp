#include "chestnut/engine/debug/editor/component_views/gui_sprite_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/log.hpp"

#include <nfd.h>


namespace chestnut::engine::debug
{
    void CGuiSpriteComponentView::fetchComponent(ecs::entityid_t entity) 
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CSpriteComponent>(entity);

        if(m_handle->sprite.getResource())
        {
            m_texturePath = m_handle->sprite.getResource()->m_texturePath.value_or("").c_str();
        }
        else
        {
            m_texturePath = "";
        }

        m_clippingRect = m_handle->sprite.getClippingRect();
        m_tint = m_handle->sprite.getTint();
        m_tintFactor = m_handle->sprite.getTintFactor();
    }

    void CGuiSpriteComponentView::drawGuiWindow() 
    {
        if(ImGui::CollapsingHeader("CSpriteComponent", ImGuiTreeNodeFlags_DefaultOpen))
        {

            ImGui::Text("Texture path");
            ImGui::InputText( "##Texture path", (char *)m_texturePath.c_str(), m_texturePath.capacity() + 1, ImGuiInputTextFlags_ReadOnly);
            ImGui::SameLine();
            if(ImGui::Button("...##browseForImage"))
            {
                nfdchar_t *filePath = NULL;
                nfdresult_t result = NFD_OpenDialog( NULL, NULL, &filePath );
                    
                if(result == NFD_OKAY) 
                {
                    auto loaded = CTexture2DResource::loadFromFile(filePath);
                    if(loaded.has_value())
                    {
                        m_handle->sprite.setResource(loaded.value());
                    }
                    else
                    {
                        //TODO add a popup for this
                        LOG_ERROR(loaded.error());
                    }

                    NFD_Free(filePath);
                }
                else if(result == NFD_ERROR)
                {
                    LOG_ERROR(NFD_GetError());   
                }
            }

            ImGui::Text("Clipping rectangle");
            ImGui::DragFloat4("##Clipping rectangle", &m_clippingRect.x);

            ImGui::Text("Tint");
            ImGui::ColorEdit3("##Tint", &m_tint.x, ImGuiColorEditFlags_Float);

            ImGui::Text("Tint factor");
            ImGui::SliderFloat("##Tint factor", &m_tintFactor, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

            ImGui::NewLine();
        }

        m_handle->sprite.setClippingRect(m_clippingRect);
        m_handle->sprite.setTint(m_tint);
        m_handle->sprite.setTintFactor(m_tintFactor);
    }

} // namespace chestnut::engine::debug

