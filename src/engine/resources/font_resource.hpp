#ifndef __CHESTNUT_FONT_RESOURCE_H__
#define __CHESTNUT_FONT_RESOURCE_H__

#include "engine/graphics/map_sprite_sheet.hpp"
#include "engine/misc/flags.hpp"

#include <string>
#include <memory>
#include <set>
#include <unordered_map>

namespace chestnut
{
    enum class EFontStyle
    {
        NORMAL,
        BOLD,
        ITALIC,
        UNDERLINE,
        STRIKETHROUGH
    };

    DECLARE_ENUM_FLAG_OPERATORS(EFontStyle)


    struct SGlyphMetrics
    {
        int width;
        int height;
        int xMin;
        int xMax;
        int yMin;
        int yMax;
        int advance;
    };
    
    struct SFontConfig
    {
        int pointSize;
        EFontStyle styleMask;
        int ascent;
        int descent;
        int height;
        CMapSpriteSheetTexture2D<wchar_t> glyphSpriteSheet;
        std::unordered_map<wchar_t, SGlyphMetrics> mapGlyphMetrics;
    };

    class CFontResource
    {
    public:
        std::string fontPath;
        std::set< wchar_t > setAvailableGlyphs;
        std::unordered_map< size_t, SFontConfig > mapConfigHashToConfig;

        CFontResource();

        CFontResource( const std::string& fontPath );


        bool isValid() const;

        // Throws an exception if resource is not valid
        void loadConfig( int pointSize, EFontStyle styleMask );

        bool hasConfig( int pointSize, EFontStyle styleMask );
        
        // Throws an exception if resource is not valid
        // Otherwise, if doesn't find a config, loads it and then returns it
        const SFontConfig& getConfig( int pointSize, EFontStyle styleMask );

        size_t getConfigHash( int pointSize, EFontStyle styleMask );
    };


    // Throws an exception if fails to load the font
    std::shared_ptr<CFontResource> loadFontResourceFromFile( const std::string& fontPath );

} // namespace chestnut

#endif // __CHESTNUT_FONT_RESOURCE_H__