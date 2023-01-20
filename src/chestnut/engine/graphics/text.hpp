#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/vector3.hpp"
#include "chestnut/engine/resources/font_resource.hpp"

#include <vector>

namespace chestnut::engine
{
    namespace internal
    {
        struct STextGlyph
        {   
            // debug
            wchar_t g;
            CFlags<EFontStyle> styleMask;

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
            EFontStyle styleMask;
            vec3f color;
        };
        
    } // namespace internal
    

    enum class ETextAlignment
    {
        LEFT,
        CENTER,
        RIGHT
    };

    class CHESTNUT_API CText
    {
    protected:
        std::shared_ptr<CFontResource> m_resource;
        int m_pointSize;

        ETextAlignment m_alignment;
        int m_maxWidth;
        float m_lineSpacing;

        std::vector<internal::STextFragmentRaw> m_vecRawFragments;
        std::vector<internal::STextLine> m_vecLines;

    public:
        CText();
        explicit CText( std::shared_ptr<CFontResource> fontResource, int pointSize );

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
        void append( std::wstring str, EFontStyle styleMask = EFontStyle::NORMAL, vec3f color = { 1.f, 1.f, 1.f } );
        void append( std::string str, EFontStyle styleMask = EFontStyle::NORMAL, vec3f color = { 1.f, 1.f, 1.f } );


        std::wstring getString() const;
        bool isEmpty() const;

        int getWidthPixels() const;
        int getHeightPixels() const;
        vec2i getSizePixels() const;


        void clearData();
        void generateData();
        const std::vector<internal::STextLine>& getData() const;


    protected:
        int computeLineHeight( const internal::STextLine& line ) const;
        int computeLineWidth( const internal::STextLine& line ) const;
        std::wstring computeLineString( const internal::STextLine& line ) const;
        int computeLineOffsetX( int maxWidth, int lineWidth ) const;
        int computeWordWidth( std::wstring word, const SFontConfig& fontConfig ) const;

        // If line with that index doesn't yet exist, it gets created
        void insertBackGlyphsIntoLineSafe( std::vector<internal::STextGlyph> vecGlyphs, unsigned int lineIdx );
        void appendWord( std::wstring str, const SFontConfig& fontConfig, vec3f color );
        void formatLines( unsigned int beginLineIdx = 0 );
        void appendFragment( std::wstring str, EFontStyle styleMask, vec3f color );
    };

} // namespace chestnut::engine

