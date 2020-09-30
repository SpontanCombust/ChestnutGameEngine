#include "engine/ecs/component_systems/rendering_component_system.hpp"

#include "engine/core/angles.hpp"
#include "engine/app/render_window.hpp"

#include <algorithm>

namespace chestnut
{
    bool CRenderingComponentSystem::needsComponents( const std::vector< std::string > compTypeStrings )
    {
        return std::any_of( compTypeStrings.begin(), compTypeStrings.end(),
            []( std::string s )
            { 
                return s == STransformComponent::getTypeStringStatic()
                    || s == STextureComponent::getTypeStringStatic();
            }
        );
    }
    
    void CRenderingComponentSystem::fetchComponents( const CComponentDatabase& dbRef )
    {
        dbRef.fillComponentMapOfType( m_transformCompMap, STransformComponent::getTypeStringStatic() );
        dbRef.fillComponentMapOfType( m_textureCompMap, STextureComponent::getTypeStringStatic() );
    }
    
    void CRenderingComponentSystem::manageCurrentComponents() 
    {
        SDL_RenderClear( CRenderWindow::getSDLRenderer() );

        transformTextures();
        drawTextures();

        SDL_RenderPresent( CRenderWindow::getSDLRenderer() ); //??? again, static rendering functions?
    }


    void CRenderingComponentSystem::transformTextures() 
    {
        uint64_t guid;
        STransformComponent *transformComp;
        STextureComponent *textureComp;
        for( auto &pair : m_transformCompMap )
        {
            guid = pair.first;
            transformComp = pair.second;

            textureComp = m_textureCompMap[guid];
            if( textureComp != nullptr )
            {
                textureComp->texture->setPosition( transformComp->position );
                textureComp->texture->setRotation( transformComp->rotation );
                textureComp->texture->setScale( transformComp->scale );
            }
        }
    }

    void CRenderingComponentSystem::drawTextures() const
    {
        STextureComponent *textureComp;
        for( const auto &pair : m_textureCompMap )
        {
            textureComp = pair.second;
            if( textureComp != nullptr )
            {
                textureComp->texture->draw(); //??? Replace with static drawing function?
            }
        }
    }

} // namespace chestnut

