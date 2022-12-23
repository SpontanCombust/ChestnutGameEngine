#include "chestnut/engine/debug/editor/component_views/gui_sprite_component_view.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"

#include <nfd.h>


namespace chestnut::engine::debug
{
    static const char * adjustToModelItems[] = {"None", "Scaled", "Spanned", "Zoomed"};
    static const char * filteringItems[] = {"Nearest", "Linear"};

    CGuiSpriteComponentView::CGuiSpriteComponentView() noexcept
    {
        m_texturePath.reserve(128);
    }

    void CGuiSpriteComponentView::fetchComponent(ecs::entityid_t entity) 
    {
        m_handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<CSpriteComponent>(entity);

        if(m_handle->sprite.getResource())
        {
            m_texturePath = m_handle->sprite.getResource()->m_location.value_or("").string();
        }
        else
        {
            m_texturePath = "";
        }

        GLint magFilter;
        m_handle->sprite.getFiltering(nullptr, &magFilter);
        if(magFilter == GL_NEAREST)
        {
            m_selectedFiltering = 0;
        }
        else if(magFilter == GL_LINEAR)
        {
            m_selectedFiltering = 1;
        }
        else
        {
            m_selectedFiltering = -1;
        }

        m_clippingRect = m_handle->sprite.getClippingRect();
        m_tint = m_handle->sprite.getTint();
        m_tintFactor = m_handle->sprite.getTintFactor();
        m_selectedAdjustToModel = (int)m_handle->adjust;
        //TODO add attribs from CTexture2D
    }

    void CGuiSpriteComponentView::drawWidgets() 
    {
        ImGui::Text("Texture path");
        ImGui::InputText( "##Texture path", (char *)m_texturePath.c_str(), m_texturePath.capacity() + 1, ImGuiInputTextFlags_ReadOnly);
        ImGui::SameLine();
        if(ImGui::Button("...##browseForImage"))
        {
            nfdchar_t *filePath = NULL;
            nfdresult_t result = NFD_OpenDialog( NULL, NULL, &filePath );

            static const std::string errBeginning("Error occured when loading a texture:\n");

            if(result == NFD_OKAY) 
            {
                //FIXME use ResourceManager
                auto loaded = CTexture2DResource::loadFromImageFile(filePath);
                if(loaded.has_value())
                {
                    m_handle->sprite.setResource(loaded.value());
                    m_clippingRect = m_handle->sprite.getClippingRect();
                }
                else
                {
                    std::string err(loaded.error());
                    LOG_ERROR(err);
                    messageBoxInfo(errBeginning + err);
                }

                NFD_Free(filePath);
            }
            else if(result == NFD_ERROR)
            {
                std::string err(NFD_GetError());
                LOG_ERROR(err);
                messageBoxInfo(errBeginning + err);
            }
        }

        ImGui::Text("Filtering");
        ImGui::Combo("##Filtering", &m_selectedFiltering, filteringItems, IM_ARRAYSIZE(filteringItems));
        if(m_selectedFiltering == 0)
        {
            m_handle->sprite.setFiltering(GL_NEAREST, GL_NEAREST);
        }
        else if(m_selectedFiltering == 1)
        {
            m_handle->sprite.setFiltering(GL_NEAREST, GL_LINEAR);
        }

        ImGui::Text("Clipping rectangle");
        ImGui::DragFloat4("##Clipping rectangle", &m_clippingRect.x);
        m_handle->sprite.setClippingRect(m_clippingRect);

        ImGui::Text("Tint");
        ImGui::ColorEdit3("##Tint", &m_tint.x, ImGuiColorEditFlags_Float);
        m_handle->sprite.setTint(m_tint);

        ImGui::Text("Tint factor");
        ImGui::SliderFloat("##Tint factor", &m_tintFactor, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
        m_handle->sprite.setTintFactor(m_tintFactor);

        ImGui::Text("Adjust to model");
        ImGui::Combo("##Adjust to model", &m_selectedAdjustToModel, adjustToModelItems, IM_ARRAYSIZE(adjustToModelItems));
        m_handle->adjust = (ESpriteToModel2DAdjust)m_selectedAdjustToModel;
    }

} // namespace chestnut::engine::debug

