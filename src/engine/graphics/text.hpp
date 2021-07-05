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
        // debug
        wchar_t g;
        EFontStyle style;

        // data
        GLuint texID;
        vec3f color;
        vec2i lineOffset;
        vec2i size;
        vec2f uvOffsetNorm;
        vec2f uvSizeNorm;
    };

    struct STextLine
    {
        // debug
        std::wstring str;

        //data
        vec2i offset;
        std::vector< STextGlyph > vecGlyphs;
    };

    struct STextFragmentRaw
    {
        std::wstring str;
        EFontStyle style;
        vec3f color;
    };

    enum class ETextAlignment
    {
        LEFT,
        CENTER,
        RIGHT
    };

    class CText
    {
    protected:
        std::shared_ptr<CFontResource> m_resource;
        int m_pointSize;

        ETextAlignment m_alignment;
        int m_maxWidth;
        float m_lineSpacing;

        std::vector<STextFragmentRaw> m_vecRawFragments;
        std::vector<STextLine> m_vecLines;

    public:
        CText();
        CText( std::shared_ptr<CFontResource> fontResource, int pointSize );

        const std::shared_ptr<CFontResource>& getResource() const;
        bool isValid() const;

        int getPointSize() const;


        void setAligment( ETextAlignment alignment );
        ETextAlignment getAlignment() const;

        // Negative number for unlimited width
        void setMaxWidthPixels( int w );
        int getMaxWidthPixels() const;

        // Set the factor of lineskip that gets multiplied by minimal line skip height
        void setLineSpacing( float spacing );
        float getLineSpacing() const;


        void clear();
        void newline();
        void append( std::wstring str, EFontStyle style = EFontStyle::NORMAL, vec3f color = { 1.f, 1.f, 1.f } );


        std::wstring getString() const;
        bool isEmpty() const;

        int getWidthPixels() const;
        int getHeightPixels() const;
        vec2i getSizePixels() const;


        void clearData();
        void generateData();
        const std::vector<STextLine>& getData() const;


    protected:
        int computeLineHeight( const STextLine& line ) const;
        int computeLineWidth( const STextLine& line ) const;
        std::wstring computeLineString( const STextLine& line ) const;
        int computeLineOffsetX( int maxWidth, int lineWidth ) const;
        int computeWordWidth( std::wstring word, const SFontConfig& fontConfig ) const;

        // If line with that index doesn't yet exist, it gets created
        void insertBackGlyphsIntoLineSafe( std::vector<STextGlyph> vecGlyphs, unsigned int lineIdx );
        void appendWord( std::wstring str, const SFontConfig& fontConfig, vec3f color );
        void formatLines( unsigned int beginLineIdx = 0 );
        void appendFragment( std::wstring str, EFontStyle style, vec3f color );
    };

} // namespace chestnut

#endif // __CHESTNUT_TEXT_H__