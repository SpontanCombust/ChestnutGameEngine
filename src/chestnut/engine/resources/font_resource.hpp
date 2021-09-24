#ifndef __CHESTNUT_ENGINE_FONT_RESOURCE_H__
#define __CHESTNUT_ENGINE_FONT_RESOURCE_H__

#include "resource.hpp"
#include "../graphics/map_sprite_sheet.hpp"
#include "../misc/flags.hpp"

#include <string>
#include <memory> // std::shared_ptr
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

    class CFontResource : public IResource
    {
    public:
        std::string m_fontPath;
        
        std::set< wchar_t > m_setAvailableGlyphs;
        std::unordered_map< size_t, SFontConfig > m_mapConfigHashToConfig;

    public:
        CFontResource();
        
        
        bool isValid() const override;


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

#endif // __CHESTNUT_ENGINE_FONT_RESOURCE_H__