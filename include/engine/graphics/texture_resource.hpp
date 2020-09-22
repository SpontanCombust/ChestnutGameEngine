#pragma once

#include "texture.hpp"
#include "engine/core/vector.hpp"

#include <SDL2/SDL_image.h>

#include <string>

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