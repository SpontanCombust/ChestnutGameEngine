#ifndef __CHESTNUT_ENGINE_FONT_RESOURCE_H__
#define __CHESTNUT_ENGINE_FONT_RESOURCE_H__

#include "chestnut/engine/macros.hpp"
#include "resource.hpp"
#include "texture2d_resource.hpp"
#include "../maths/rectangle.hpp"
#include "../misc/flags.hpp"

#include <string>
#include <map>
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

    class CHESTNUT_API CFontResource : public IResource
    {
    public:
        std::string m_fontPath;
        
        std::unordered_map< size_t, SFontConfig > m_mapConfigHashToConfig;

    public:
        CFontResource() noexcept;
        
        ~CFontResource() noexcept;


        bool loadConfig( int pointSize, EFontStyle styleMask ) noexcept;

        bool hasConfig( int pointSize, EFontStyle styleMask ) noexcept;
        
        // TODO optional reference wrapper
        const SFontConfig& getConfig( int pointSize, EFontStyle styleMask ) noexcept;

        size_t getConfigHash( int pointSize, EFontStyle styleMask ) noexcept;


        // fontPath - path to .ttf file
        static tl::expected<std::shared_ptr<CFontResource>, const char *> loadFromFile( const char *fontPath ) noexcept;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_FONT_RESOURCE_H__