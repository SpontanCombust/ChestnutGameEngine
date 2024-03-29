#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/resources/texture2d_resource.hpp"
#include "chestnut/engine/maths/rectangle.hpp"
#include "chestnut/engine/misc/flags.hpp"

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
        CFlags<EFontStyle> styleMask;
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
        std::unordered_map< size_t, SFontConfig > m_mapConfigHashToConfig;

    public:
        bool loadConfig( int pointSize, CFlags<EFontStyle> styleMask ) noexcept;

        bool hasConfig( int pointSize, CFlags<EFontStyle> styleMask ) noexcept;
        
        const SFontConfig& getConfig( int pointSize, CFlags<EFontStyle> styleMask ) noexcept;

        size_t getConfigHash( int pointSize, CFlags<EFontStyle> styleMask ) noexcept;


        // fontPath - path to .ttf file
        static tl::expected<std::shared_ptr<CFontResource>, std::string> 
        load(std::filesystem::path fontPath) noexcept;

    private:
        CFontResource(std::filesystem::path location) noexcept;
    };

} // namespace chestnut::engine

