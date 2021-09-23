#include "font_resource.hpp"

#include "../misc/exception.hpp"
#include "../debug/debug.hpp"
#include "../resources/texture2d_resource.hpp"

#include <SDL2/SDL_ttf.h>

#include <cmath> // ceil, sqrt
#include <map>
#include <utility> // pair
#include <vector>

namespace chestnut
{
    DEFINE_ENUM_FLAG_OPERATORS(EFontStyle)


    int convertToSDLFontStyle( EFontStyle styleMask )
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

    std::vector< std::pair< wchar_t, wchar_t > > getUnicodeValueRanges()
    {
        std::vector< std::pair< wchar_t, wchar_t > > vecValueRanges;

        // basic latin
        vecValueRanges.push_back( std::make_pair( 0x0020, 0x007F ) );
        // latin 1 supplement
        vecValueRanges.push_back( std::make_pair( 0x00A1, 0x00FF ) );
        // latin extended A
        vecValueRanges.push_back( std::make_pair( 0x0100, 0x017F ) );
        // latin extended B
        vecValueRanges.push_back( std::make_pair( 0x0180, 0x024F ) );

        return vecValueRanges;
    }

    SFontConfig loadConfigInternal( TTF_Font *font, int pointSize, EFontStyle styleMask, const std::vector< std::pair< wchar_t, wchar_t > >& vecUnicodeRanges )
    {
        int sdlStyle = convertToSDLFontStyle( styleMask );
        TTF_SetFontStyle( font, sdlStyle );



        // ========== render all glyphs into seperate surfaces and get their metrics ==========

        std::map< wchar_t, SDL_Surface * > mapGlyphSurfaces;
        std::unordered_map< wchar_t, SGlyphMetrics > mapGlyphMetrics;
        int maxGlyphSideLength = 0;
        for( const auto& [ first, last ] : vecUnicodeRanges )
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

                    mapGlyphMetrics[g] = metrics;
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

        std::map< wchar_t, SRectangle > mapClippingRects;

        int x = 0, y = 0;
        for( const auto& [ g, surf ] : mapGlyphSurfaces )
        {
            SDL_Rect dstRect = { x, y, surf->w, surf->h };

            SDL_BlitSurface( surf, NULL, spriteSheetSurface, &dstRect );
            mapClippingRects[g] = SRectangle( x, y, surf->w, surf->h );
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

        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        std::shared_ptr<CTexture2DResource> textureResource = loadTexture2DResourceFromPixels( alphaPixels8, spriteSheetSideLength, spriteSheetSideLength, GL_RED );
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

        delete alphaPixels8;


        // ========== create the font config ==========

        SFontConfig config;
        config.pointSize = pointSize;
        config.styleMask = styleMask;
        config.ascent = TTF_FontAscent( font );
        config.descent = TTF_FontDescent( font );
        config.height = TTF_FontHeight( font );
        config.mapGlyphMetrics = mapGlyphMetrics;
        config.glyphSpriteSheet = CMapSpriteSheetTexture2D<wchar_t>( textureResource );
        config.glyphSpriteSheet.setSheetFragments( mapClippingRects );


        return config;
    }

    size_t getConfigHashInternal( int pointSize, EFontStyle styleMask ) 
    {
        std::hash<std::string> hasher;

        size_t pointSizeHash = hasher( std::to_string( pointSize ) );
        size_t styleHash = hasher( std::to_string( static_cast<int>( styleMask ) ) );

        return pointSizeHash ^ styleHash;
    }

    



    CFontResource::CFontResource() 
    {
        m_fontPath = "";
    }

    bool CFontResource::isValid() const
    {
        if( !m_mapConfigHashToConfig.empty() )
        {
            return true;
        }
        return false;
    }

    void CFontResource::loadConfig( int pointSize, EFontStyle styleMask ) 
    {
        if( !isValid() )
        {
            throw ChestnutException( "Font resource is not valid!" );
        }

        if( !hasConfig( pointSize, styleMask ) )
        {
            TTF_Font *font = TTF_OpenFont( m_fontPath.c_str(), pointSize );
            auto unicodeValues = getUnicodeValueRanges();

            SFontConfig config = loadConfigInternal( font, pointSize, styleMask, unicodeValues );
            size_t hash = getConfigHash( pointSize, styleMask );
            m_mapConfigHashToConfig[ hash ] = config;

            TTF_CloseFont( font );
        }
    }

    bool CFontResource::hasConfig( int pointSize, EFontStyle styleMask ) 
    {
        if( !isValid() )
        {
            return false;
        }

        size_t hash = getConfigHash( pointSize, styleMask );

        auto it = m_mapConfigHashToConfig.find( hash );
        auto end = m_mapConfigHashToConfig.end();

        if( it != end )
        {
            return true;
        }
        return false;
    }

    const SFontConfig& CFontResource::getConfig( int pointSize, EFontStyle styleMask ) 
    {
        // let the exception propagate if it happens
        // checks for whether config is already loaded are already in that function
        loadConfig( pointSize, styleMask );

        size_t hash = getConfigHash( pointSize, styleMask );
        return m_mapConfigHashToConfig[ hash ];
    }

    size_t CFontResource::getConfigHash( int pointSize, EFontStyle styleMask ) 
    {
        return getConfigHashInternal( pointSize, styleMask );
    }




    #define INIT_FONT_POINT_SIZE 16
    #define INIT_FONT_STYLE EFontStyle::NORMAL

    std::shared_ptr<CFontResource> loadFontResourceFromFile( const std::string& fontPath ) 
    {
        TTF_Font *font = TTF_OpenFont( fontPath.c_str(), INIT_FONT_POINT_SIZE );

        if( font )
        {
            auto unicodeValues = getUnicodeValueRanges();
            SFontConfig initConfig = loadConfigInternal( font, INIT_FONT_POINT_SIZE, INIT_FONT_STYLE, unicodeValues );
            size_t hash = getConfigHashInternal( INIT_FONT_POINT_SIZE, INIT_FONT_STYLE );

            CFontResource *resource = new CFontResource();
            resource->m_fontPath = fontPath;
            resource->m_mapConfigHashToConfig[ hash ] = initConfig;
            for( const auto& [ g, metrics ] : initConfig.mapGlyphMetrics )
            {
                resource->m_setAvailableGlyphs.insert(g);
            }

            TTF_CloseFont( font );

            return std::shared_ptr<CFontResource>( resource );
        }        
        else
        {
            throw ChestnutException( "Failed to load font from file " + fontPath );
        }
    }

} // namespace chestnut`
