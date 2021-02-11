#include "renderer.hpp"

#include "engine/maths/angles.hpp"
#include "engine/misc/utils.hpp"

namespace chestnut
{
    SDL_Renderer *CRenderer::m_sdlRenderer = nullptr;
    
    void CRenderer::setSDLRenderer( SDL_Renderer *renderer ) 
    {
        m_sdlRenderer = renderer;
    }


    SDL_Renderer* CRenderer::getSDLRenderer() 
    {
        return m_sdlRenderer;
    }

    void CRenderer::renderTexture( const CTexture& texture ) 
    {
        if( !texture.getSDLTexturePtr() )
        {
            throw ChestnutException( "A texture with nullptr to SDL_Texture can't be rendered!" );
        }

        SDL_Rect srcRect;
        SDL_FRect dstRect;
        double angle;
        SDL_FPoint center;
        SDL_RendererFlip flip;

        srcRect = 
        { 
            texture.getClippingRectPos().x,
            texture.getClippingRectPos().y,
            texture.getClippingRectSize().x,
            texture.getClippingRectSize().y
        };

        dstRect =
        {
            texture.getPosition().x,
            texture.getPosition().y,
            texture.getSize().x,
            texture.getSize().y
        };

        // negative because positive rotation in SDL means clockwise as opposed to the rotation in traditional cartesian system
        angle = -radiansToDegrees( texture.getRotationRad() );

        center =
        {
            (float)( texture.getRotationPoint().x * texture.getSize().x ),
            (float)( texture.getRotationPoint().y * texture.getSize().y )
        };

        flip = texture.getFlip();

        SDL_RenderCopyExF( m_sdlRenderer,
                            texture.getSDLTexturePtr(),
                            &srcRect, 
                            &dstRect, 
                            angle, 
                            &center, 
                            flip 
                        );
    }

    void CRenderer::renderPresent() 
    {
        SDL_RenderPresent( m_sdlRenderer );
    }

    void CRenderer::renderClear() 
    {
        SDL_RenderClear( m_sdlRenderer );
    }
    
} // namespace chestnut
