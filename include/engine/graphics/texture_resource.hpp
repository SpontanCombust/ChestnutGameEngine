#pragma once

#include <SDL2/SDL_image.h>

#include <string>

#include "core/vector.hpp"
#include "texture.hpp"

namespace engine { namespace graphics {

    class CTexture; //forward declaration

    class CTextureResource
    {
        private:
            friend class CTexture;
            SDL_Texture *m_sdlTexture;

        public:
            CTextureResource( const std::string path, SDL_Renderer *renderer ); //TODO get rid of the renderer argument
            ~CTextureResource();

            void loadFromFile( const std::string path, SDL_Renderer *renderer );
            vector::Vector2i getSize() const;

            CTexture getTextureInstance() const;
    };

}}