#include "font_resource.hpp"

#include "../debug/log.hpp"
#include "../resources/texture2d_resource.hpp"
#include "../macros.hpp"

#include <SDL_ttf.h>

#include <array>
#include <cmath> // ceil, sqrt
#include <map>
#include <utility> // pair

namespace chestnut::engine
{
    DEFINE_ENUM_FLAG_OPERATORS(EFontStyle)


    static int convertToSDLFontStyle( EFontStyle styleMask ) noexcept
    {
        int sdlStyle = 0;

        if( ( styleMask & EFontStyle::NORMAL ) == EFontStyle::NORMAL )
        {
            sdlStyle |= TTF_STYLE_NORMAL;   
        }
        if( ( styleMask & EFontStyle::BOLD ) == EFontStyle::BOLD )
        {
            sdlStyle |= TTF_STYLE_BOLD;   
        }
        if( ( styleMask & EFontStyle::ITALIC ) == EFontStyle::ITALIC )
        {
            sdlStyle |= TTF_STYLE_ITALIC;   
        }
        if( ( styleMask & EFontStyle::UNDERLINE ) == EFontStyle::UNDERLINE )
        {
            sdlStyle |= TTF_STYLE_UNDERLINE;   
        }
        if( ( styleMask & EFontStyle::STRIKETHROUGH ) == EFontStyle::STRIKETHROUGH )
        {
            sdlStyle |= TTF_STYLE_STRIKETHROUGH;   
        }
        
        return sdlStyle;
    }

    constexpr std::array< std::pair< wchar_t, wchar_t >, 4 > unicodeValueRanges = {{
        { 0x0020, 0x007F },
        { 0x00A1, 0x00FF },
        { 0x0100, 0x017F },
        { 0x0180, 0x024F }
    }};

    SFontConfig loadConfigInternal( TTF_Font *font, int pointSize, EFontStyle styleMask ) noexcept
    {
        SFontConfig config;

        int sdlStyle = convertToSDLFontStyle( styleMask );
        TTF_SetFontStyle( font, sdlStyle );

        config.pointSize = pointSize;
        config.styleMask = styleMask;
        config.ascent = TTF_FontAscent( font );
        config.descent = TTF_FontDescent( font );
        config.height = TTF_FontHeight( font );


        // ========== render all glyphs into seperate surfaces and get their metrics ==========

        std::map< wchar_t, SDL_Surface * > mapGlyphSurfaces;
        int maxGlyphSideLength = 0;
        for( const auto& [ first, last ] : unicodeValueRanges )
        {
            for (wchar_t g = first; g <= last; g++)
            {
                SDL_Surface *surf = TTF_RenderGlyph_Blended( font, (Uint16)g, { 0, 0, 0 } ); // we care only about alpha component in color
                if( surf )
                {
                    if( surf->h > maxGlyphSideLength )
                    {
                        maxGlyphSideLength = surf->h;
                    }
                    if( surf->w > maxGlyphSideLength )
                    {
                        maxGlyphSideLength = surf->w;
                    }

                    SGlyphMetrics metrics;
                    metrics.width = surf->w;
                    metrics.height = surf->h;
                    TTF_GlyphMetrics( font, (Uint16)g, &metrics.xMin, &metrics.xMax, &metrics.yMin, &metrics.yMax, &metrics.advance );

                    config.mapGlyphMetrics[g] = metrics;
                    mapGlyphSurfaces[g] = surf;
                }
            }
        }



        // ========== algorithm calculating the side length of the spritesheet texture ==========
        // it takes the total number of glyph surfaces and calulates the ceiling of its square root
        // this gives the normalized side length of the theoretical square which could fit all these surfaces if they were 1x1 squares
        // then it's multiplied by the maximal side length of all these surfaces, so it guarantess all of them could fit onto a single texture
        int spriteSheetSideLength = std::ceil( std::sqrt( mapGlyphSurfaces.size() ) ) * maxGlyphSideLength;


        SDL_Surface *spriteSheetSurface = SDL_CreateRGBSurface( 0, spriteSheetSideLength, spriteSheetSideLength, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000 );




        // ========== blit all glyph surfaces onto a single bigger surface ==========

        int x = 0, y = 0;
        for( const auto& [ g, surf ] : mapGlyphSurfaces )
        {
            SDL_Rect dstRect = { x, y, surf->w, surf->h };

            SDL_BlitSurface( surf, NULL, spriteSheetSurface, &dstRect );
            config.mapGlyphClippingRects[g] = SRectangle( x, y, surf->w, surf->h );
            SDL_FreeSurface( surf );

            x += maxGlyphSideLength;
            // check if current X position allows for blitting
            // if not, move to next row and reset X
            if( x > ( spriteSheetSideLength - maxGlyphSideLength ) )
            {
                y += maxGlyphSideLength;
                x = 0;
            }
        }



        // ========== extract alpha from the sprite sheet surface ==========

        uint32_t *argbPixels = (uint32_t *)spriteSheetSurface->pixels;
        uint32_t pixelCount = spriteSheetSideLength * spriteSheetSideLength; 
        uint32_t alphaPixel32;
        uint8_t *alphaPixels8 = new uint8_t[ pixelCount ]; // 1 byte (alpha) per pixel
        for (uint32_t i = 0; i < pixelCount; i++)
        {
            // byte shift the ARGB pixel to right by 3 bytes
            // the result of this is the value of alpha component
            // if we shift ARGB by 3 bytes to right all we get left is A
            alphaPixel32 = ( argbPixels[i] >> 24 );
            alphaPixels8[i] = (uint8_t)( alphaPixel32 );
        }

        SDL_FreeSurface( spriteSheetSurface );
        


        // ========== create the OpenGL texture resource ==========
        if(auto spritesheetTexture = CTexture2DResource::loadFromPixels(alphaPixels8, spriteSheetSideLength, spriteSheetSideLength, 1) )
        {
            config.textureResource = *spritesheetTexture;
        }
        else
        {
            LOG_WARNING("Failed to create texture resource from font spritesheet");
        }
        
        delete[] alphaPixels8; // we won't need it no more, data is copied to the GPU

        return config;
    }

    size_t getConfigHashInternal( int pointSize, EFontStyle styleMask ) noexcept
    {
        static std::hash<std::string> hasher;

        size_t pointSizeHash = hasher( std::to_string( pointSize ) );
        size_t styleHash = hasher( std::to_string( static_cast<int>( styleMask ) ) );

        return pointSizeHash ^ styleHash;
    }

    



    CFontResource::CFontResource() noexcept
    {
        m_fontPath = "";
    }

    CFontResource::~CFontResource() noexcept
    {
        m_mapConfigHashToConfig.clear();
    }

    bool CFontResource::loadConfig( int pointSize, EFontStyle styleMask ) noexcept
    {
        if( !hasConfig( pointSize, styleMask ) )
        {
            TTF_Font *font = TTF_OpenFont( m_fontPath.c_str(), pointSize );

            SFontConfig config = loadConfigInternal( font, pointSize, styleMask );
            size_t hash = getConfigHash( pointSize, styleMask );
            m_mapConfigHashToConfig[ hash ] = config;

            TTF_CloseFont( font );
            return true;
        }

        return false;
    }

    bool CFontResource::hasConfig( int pointSize, EFontStyle styleMask ) noexcept
    {
        size_t hash = getConfigHash( pointSize, styleMask );

        auto it = m_mapConfigHashToConfig.find( hash );
        auto end = m_mapConfigHashToConfig.end();

        if( it != end )
        {
            return true;
        }
        return false;
    }

    const SFontConfig& CFontResource::getConfig( int pointSize, EFontStyle styleMask ) noexcept
    {
        // checks for whether config is already loaded are already in that function
        loadConfig( pointSize, styleMask );

        size_t hash = getConfigHash( pointSize, styleMask );
        return m_mapConfigHashToConfig[ hash ];
    }

    size_t CFontResource::getConfigHash( int pointSize, EFontStyle styleMask ) noexcept
    {
        return getConfigHashInternal( pointSize, styleMask );
    }



    tl::expected<std::shared_ptr<CFontResource>, const char *> CFontResource::loadFromFile(const char *fontPath) noexcept
    {
        LOG_INFO( "Loading font resource from file: " << fontPath );

        TTF_Font *font = TTF_OpenFont( fontPath, CHESTNUT_FONT_RESOURCE_INIT_FONT_POINT_SIZE );

        if( font )
        {
            SFontConfig initConfig = loadConfigInternal( font, CHESTNUT_FONT_RESOURCE_INIT_FONT_POINT_SIZE, CHESTNUT_FONT_RESOURCE_INIT_FONT_STYLE );
            size_t hash = getConfigHashInternal( CHESTNUT_FONT_RESOURCE_INIT_FONT_POINT_SIZE, CHESTNUT_FONT_RESOURCE_INIT_FONT_STYLE );

            CFontResource *resource = new CFontResource();
            resource->m_fontPath = fontPath;
            resource->m_mapConfigHashToConfig[ hash ] = initConfig;

            TTF_CloseFont( font );

            return std::shared_ptr<CFontResource>( resource );
        }        
        else
        {
            return tl::make_unexpected<const char *>("Failed to load font from file");
        }
    }

} // namespace chestnut::engine`
