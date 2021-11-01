#ifndef __CHESTNUT_ENGINE_FONT_RESOURCE_H__
#define __CHESTNUT_ENGINE_FONT_RESOURCE_H__

#include "resource.hpp"
#include "texture2d_resource.hpp"
#include "../maths/rectangle.hpp"
#include "../misc/flags.hpp"

#include <string>
#include <map>
#include <memory> // std::shared_ptr
#include <set>
#include <unordered_map>

namespace chestnut::engine
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
        std::shared_ptr<CTexture2DResource> textureResource; // has a texture with all of the glyphs
        std::map< wchar_t, SRectangle > mapGlyphClippingRects; // has non-normalized data of placement of glyphs on the texture
        std::unordered_map<wchar_t, SGlyphMetrics> mapGlyphMetrics;
    };

    class CFontResource : public IResource
    {
    public:
        std::string m_fontPath;
        
        std::unordered_map< size_t, SFontConfig > m_mapConfigHashToConfig;

    public:
        CFontResource();
        
        ~CFontResource();


        // Throws an exception if resource is not valid
        void loadConfig( int pointSize, EFontStyle styleMask );

        bool hasConfig( int pointSize, EFontStyle styleMask );
        
        // Throws an exception if resource is not valid
        // Otherwise, if doesn't find a config, loads it and then returns it
        const SFontConfig& getConfig( int pointSize, EFontStyle styleMask );

        size_t getConfigHash( int pointSize, EFontStyle styleMask );
    };


    // fontPath - path to .ttf file
    // Throws ChestnutResourceLoadException if fails to load the font
    std::shared_ptr<CFontResource> loadFontResourceFromFile( const std::string& fontPath );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_FONT_RESOURCE_H__