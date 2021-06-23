#ifndef __CHESTNUT_TEXT_H__
#define __CHESTNUT_TEXT_H__

#include "engine/maths/vector2.hpp"
#include "engine/maths/vector4.hpp"
#include "engine/resources/font_resource.hpp"

#include <vector>

namespace chestnut
{
    struct STextGlyph
    {
        wchar_t g;
        vec2f posOffset;
        vec2f size;
        vec2f uvOffsetNorm;
        vec2f uvSizeNorm;
    };

    struct STextFragment
    {
        std::wstring str;
        EFontStyle style; 
        vec4f color;
        GLuint texID;
        std::vector< STextGlyph > vecGlyphs;
    };

    enum class ETextPositioningMode
    {
        TOP,
        BASELINE,
        BOTTOM
    };

    class CText
    {
    protected:
        std::shared_ptr<CFontResource> m_resource;
        int m_pointSize;

        ETextPositioningMode m_positioningMode;
        vec2f m_currentGlyphOffset;

        std::vector<STextFragment> m_vecFragments;

    public:
        CText();
        CText( std::shared_ptr<CFontResource> fontResource, int pointSize );

        bool isValid() const;

        int getPointSize() const;

        // Sets the relative positioning of glyphs for the text line
        void setPositioningMode( ETextPositioningMode mode );
        ETextPositioningMode getPositioningMode() const;

        void clear();
        void append( std::wstring s, EFontStyle style = EFontStyle::NORMAL, vec4f color = { 1.f, 1.f, 1.f, 1.f } );

        std::wstring getString() const;
        bool isEmpty() const;
        int getLength() const;

        float getWidth() const;
        float getHeight() const;
        vec2f getSize() const; 

        const std::vector< STextFragment >& getFragments() const;
    };

} // namespace chestnut

#endif // __CHESTNUT_TEXT_H__