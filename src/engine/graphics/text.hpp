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
        GLuint texID;
        vec4f color;
        std::vector< STextGlyph > vecGlyphs;
    };

    class CText
    {
    protected:
        std::shared_ptr<CFontResource> m_resource;

        int m_pointSize;
        std::vector<STextFragment> m_vecFragments;

        vec2f m_currentGlyphOffset;

    public:
        CText();
        CText( std::shared_ptr<CFontResource> fontResource, int pointSize );

        bool isValid() const;

        int getPointSize() const;

        void clear();

        std::wstring getString() const;

        bool isEmpty() const;
        int getLength() const;

        const std::vector< STextFragment >& getFragments() const;


        virtual void appendString( std::wstring s, EFontStyle style = EFontStyle::NORMAL, vec4f color = { 1.f, 1.f, 1.f, 1.f } );
    };

} // namespace chestnut

#endif // __CHESTNUT_TEXT_H__