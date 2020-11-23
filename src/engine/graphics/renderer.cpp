#include "engine/graphics/renderer.hpp"

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
        SDL_RenderCopyExF( m_sdlRenderer,
                            texture.getSDLTexturePtr(),
                            &texture.getSDLSrcRect(), 
                            &texture.getSDLDstRect(), 
                            texture.getSDLAngle(), 
                            &texture.getSDLRotPoint(), 
                            texture.getSDLFlip() 
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
