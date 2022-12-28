#include "chestnut/engine/graphics/text.hpp"

#include "chestnut/engine/debug/log.hpp"

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <locale>
#include <codecvt>


std::wstring_convert< std::codecvt_utf8<wchar_t> > wstringConverter;

namespace chestnut::engine
{
    using namespace internal;
    

    CText::CText() 
    {
        m_pointSize = 0;
        m_alignment = ETextAlignment::LEFT;
        m_maxWidth = -1;
        m_lineSpacing = 1.f;
    }

    CText::CText( std::shared_ptr<CFontResource> fontResource, int pointSize ) 
    {
        m_resource = fontResource;
        m_pointSize = pointSize;
        m_alignment = ETextAlignment::LEFT;
        m_maxWidth = -1;
        m_lineSpacing = 1.f;
    }

    const std::shared_ptr<CFontResource>& CText::getResource() const
    {
        return m_resource;
    }

    bool CText::isValid() const
    {
        if( m_resource )
        {
            return true;
        }
        return false;
    }

    int CText::getPointSize() const
    {
        return m_pointSize;
    }

    


    void CText::setAligment( ETextAlignment alignment ) 
    {
        m_alignment = alignment;
    }

    ETextAlignment CText::getAlignment() const
    {
        return m_alignment;
    }

    void CText::setMaxWidthPixels( int w ) 
    {
        m_maxWidth = w;
    }

    int CText::getMaxWidthPixels() const
    {
        return m_maxWidth;
    }

    void CText::setLineSpacing( float linespacing ) 
    {
        m_lineSpacing = linespacing;
    }

    float CText::getLineSpacing() const
    {
        return m_lineSpacing;
    }





    const wchar_t UNAVAILABLE_GLYPH_REPLACEMENT_WCHAR = L' ';

    // If metrics doesn't have that glyph returns replacement metrics
    const SGlyphMetrics& getGlyphMetricsSafe( const SFontConfig& config, wchar_t g )
    {
        auto it = config.mapGlyphMetrics.find(g);
        auto end = config.mapGlyphMetrics.end();

        if( it != end )
        {
            return config.mapGlyphMetrics.at(g);
        }
        else
        {
            return config.mapGlyphMetrics.at( UNAVAILABLE_GLYPH_REPLACEMENT_WCHAR );
        }
    }

    // For very long words that don't fit within maxWidth
    std::vector< std::wstring > partitionWord( std::wstring word, const SFontConfig& fontConfig, int maxFragmentWidth )
    {
        std::vector< std::wstring > vecWordFragments;

        int width = 0;
        std::wstring frag = L"";
        
        for(unsigned int i = 0; i < word.length(); i++)
        {
            const SGlyphMetrics& metrics = getGlyphMetricsSafe( fontConfig, word[i] );

            width += metrics.advance;
            frag += word[i];

            if( width > maxFragmentWidth )
            {
                vecWordFragments.push_back( frag );
                width = 0;
                frag = L"";
            }
        }

        // push back remaining fragment if there is one
        if( frag != L"" )
        {
            vecWordFragments.push_back( frag );
        }

        return vecWordFragments;
    }

    SRectangle normalizeGlyphRect( const SRectangle& rect, float spriteSheetW, float spriteSheetH )
    {
        return SRectangle( rect.x / spriteSheetW, rect.y / spriteSheetH, rect.w / spriteSheetW, rect.h / spriteSheetH );
    }

    std::vector< STextGlyph > createWordTextGlyphs( std::wstring word, const SFontConfig& fontConfig, vec3f color, vec2i baseOffset = { 0, 0 } )
    {
        std::vector< STextGlyph > vecGlyphs;

        float w = (float)fontConfig.textureResource->m_width;
        float h = (float)fontConfig.textureResource->m_height;

        STextGlyph glyph;
        vec2i offset = baseOffset;

        for( wchar_t g : word )
        {
            SGlyphMetrics metrics;
            SRectangle rectNorm;
            if( fontConfig.mapGlyphClippingRects.find(g) != fontConfig.mapGlyphClippingRects.end() )
            {
                metrics = fontConfig.mapGlyphMetrics.at(g);
                rectNorm = normalizeGlyphRect( fontConfig.mapGlyphClippingRects.at(g), w, h );
            }
            else
            {
                metrics = fontConfig.mapGlyphMetrics.at( UNAVAILABLE_GLYPH_REPLACEMENT_WCHAR );
                rectNorm = normalizeGlyphRect( fontConfig.mapGlyphClippingRects.at( UNAVAILABLE_GLYPH_REPLACEMENT_WCHAR ), w, h );
            }
            

            glyph.g = g;
            glyph.styleMask = fontConfig.styleMask;
            glyph.color = color;

            glyph.texID = fontConfig.textureResource->m_texID;
            glyph.lineOffset = { offset.x + metrics.xMin, offset.y };
            glyph.size = { metrics.width, metrics.height };
            glyph.uvOffsetNorm = { rectNorm.x, rectNorm.y };
            glyph.uvSizeNorm = { rectNorm.w, rectNorm.h };

            vecGlyphs.push_back( glyph );

            offset += { metrics.advance, 0 };
        } 

        return vecGlyphs;       
    }

    std::vector< std::wstring > tokenizeString( std::wstring str, wchar_t separator, bool includeSeparator = false )
    {
        // size_t separatorPos;
        bool isSeparatorPrev = false, isSeparatorCurrent = false;
        std::wstring substr;
        std::vector< std::wstring > vecTokens;

        if( str != L"" )
        {
            for (unsigned int i = 0; i < str.length(); i++)
            {
                if( str[i] == separator )
                {
                    isSeparatorCurrent = true;
                }
                else
                {
                    isSeparatorCurrent = false;
                }

                if( isSeparatorCurrent != isSeparatorPrev )
                {
                    if( substr != L"" )
                    {
                        if( substr[0] != separator || includeSeparator )
                        {
                            vecTokens.push_back( substr );
                        }

                        substr = L"";
                    }
                }

                substr += str[i];

                isSeparatorPrev = isSeparatorCurrent;
            }
            
            // push one last remaining token
            if( substr[0] != separator || includeSeparator )
            {
                vecTokens.push_back( substr );
            }
        }

        return vecTokens;
    }




    

    int CText::computeLineHeight( const STextLine& line ) const
    {
        int height = 0;
        if( !line.vecGlyphs.empty() )
        {
            for( const STextGlyph& glyph : line.vecGlyphs )
            {
                if( glyph.lineOffset.y + glyph.size.y > height )
                {
                    height = glyph.lineOffset.y + glyph.size.y;
                }
            }
        }

        return height;
    }

    int CText::computeLineWidth( const STextLine& line ) const
    {
        int width = 0;
        if( !line.vecGlyphs.empty() )
        {
            const STextGlyph& lastGlyph = line.vecGlyphs.back();
            const SFontConfig& lastGlyphConfig = m_resource->getConfig( m_pointSize, lastGlyph.styleMask );
            const SGlyphMetrics& lastGlyphMetrics = getGlyphMetricsSafe( lastGlyphConfig, lastGlyph.g );

            width = lastGlyph.lineOffset.x + lastGlyphMetrics.advance;
        }

        return width;
    }

    std::wstring CText::computeLineString( const STextLine& line ) const
    {
        std::wstring str;

        for( const auto& glyph : line.vecGlyphs )
        {
            str += glyph.g;
        }

        return str;
    }

    int CText::computeLineOffsetX( int lineWidth, int maxWidth ) const
    {
        switch( m_alignment )
        {
            case ETextAlignment::CENTER:
                return ( maxWidth - lineWidth ) / 2;
            case ETextAlignment::RIGHT:
                return maxWidth - lineWidth;
            default:
                return 0;
        }
    }

    int CText::computeWordWidth( std::wstring word, const SFontConfig& fontConfig ) const
    {
        int width = 0;

        for( wchar_t g : word )
        {
            const SGlyphMetrics& metrics = getGlyphMetricsSafe( fontConfig, g );

            width += metrics.advance;
        }

        return width;
    }




    void CText::insertBackGlyphsIntoLineSafe( std::vector<STextGlyph> vecGlyphs, unsigned int lineIdx ) 
    {
        if( lineIdx >= vecGlyphs.size() )
        {
            m_vecLines.resize( lineIdx + 1 );
        }

        auto& vecLineGlyphs = m_vecLines[ lineIdx ].vecGlyphs;
        vecLineGlyphs.insert( vecLineGlyphs.end(), vecGlyphs.begin(), vecGlyphs.end() );
    }

    void CText::appendWord( std::wstring word, const SFontConfig& fontConfig, vec3f color ) 
    {
        if( m_vecLines.empty() )
        {
            // make sure that there is at least one available line to write into
            m_vecLines.emplace_back();
        }
        
        int lastLineIdx = m_vecLines.size() - 1;

        std::vector< STextGlyph > vecGlyphs;
        vec2i offset;

        // if the width of the text is limited
        if( m_maxWidth > 0 )
        {
            int lineWidth = computeLineWidth( m_vecLines[ lastLineIdx ] );
            int wordWidth = computeWordWidth( word, fontConfig );

            // the word won't fit in current line, create a new one and move onto it
            // also check if word is not a empty space word (a substring tokenizer returned that consists only of space(s))
            // if it would be there is no need for moving into next line as it literally consists of no visible letters
            if( lineWidth > 0 && lineWidth + wordWidth > m_maxWidth && word[0] != L' ' )
            {
                m_vecLines.emplace_back();
                lastLineIdx++;
            }

            
            // the word is too long to fit in a single line, divide it into fitting pieces
            if( wordWidth > m_maxWidth )
            {
                std::vector< std::wstring > vecWordFragments = partitionWord( word, fontConfig, m_maxWidth );

                offset = { computeLineWidth( m_vecLines[ lastLineIdx ] ), 0 };
                vecGlyphs = createWordTextGlyphs( vecWordFragments[0], fontConfig, color, offset );
                insertBackGlyphsIntoLineSafe( vecGlyphs, lastLineIdx );

                for (unsigned int i = 1; i < vecWordFragments.size(); i++)
                {
                    m_vecLines.emplace_back();
                    lastLineIdx++;

                    offset = { computeLineWidth( m_vecLines[ lastLineIdx ] ), 0 };
                    vecGlyphs = createWordTextGlyphs( vecWordFragments[i], fontConfig, color, offset );
                    insertBackGlyphsIntoLineSafe( vecGlyphs, lastLineIdx );
                }
            }
            else
            {
                offset = { computeLineWidth( m_vecLines[ lastLineIdx ] ), 0 };
                vecGlyphs = createWordTextGlyphs( word, fontConfig, color, offset );
                insertBackGlyphsIntoLineSafe( vecGlyphs, lastLineIdx );
            }
        }
        else
        {
            offset = { computeLineWidth( m_vecLines[ lastLineIdx ] ), 0 };
            vecGlyphs = createWordTextGlyphs( word, fontConfig, color, offset );
            insertBackGlyphsIntoLineSafe( vecGlyphs, lastLineIdx );   
        }
    }

    void CText::appendFragment( std::wstring str, EFontStyle styleMask, vec3f color ) 
    {
        if( str == L"" )
        {
            return;
        }

        const SFontConfig& config = m_resource->getConfig( m_pointSize, styleMask );

        auto vecNewLines = tokenizeString( str, L'\n', true );

        for( std::wstring newLine : vecNewLines )
        {
            if( newLine[0] == L'\n' )
            {
                // this new line token consists of only new line character(s)
                // so we just append as many new empty lines as is the size of this token 

                for(unsigned int i = 0; i < newLine.length(); i++)
                {
                    m_vecLines.emplace_back();
                }
            }
            else
            {
                // this new line token consists of words seperated optionally by space
                // we break it apart into these words and spaces and append them this way

                auto vecWords = tokenizeString( newLine, L' ', true );
                
                for( std::wstring word : vecWords )
                {
                    appendWord( word, config, color );
                }
            }
        }
    }

    void CText::formatLines( unsigned int beginLineIdx ) 
    {
        int currLineWidth;
        int maxWidth = 0;

        // there is no limit to actual width, so we need to calculate it based on max width of all lines
        if( m_maxWidth < 0 )
        {
            maxWidth = getWidthPixels();
        }
        else
        {
            maxWidth = m_maxWidth;
        }
        

        // first line is a special case as it doesn't need to calculate its Y offset - it's always 0
        if( beginLineIdx == 0 )
        {
            if( !m_vecLines[0].vecGlyphs.empty() )
            {
                currLineWidth = computeLineWidth( m_vecLines[0] );

                m_vecLines[0].str = computeLineString( m_vecLines[0] );
                m_vecLines[0].offset.x = computeLineOffsetX( currLineWidth, maxWidth );
                m_vecLines[0].offset.y = 0;
            }

            beginLineIdx++;
        }


        int prevLineHeight;
        int initHeight = m_resource->getConfig( m_pointSize, EFontStyle::NORMAL ).height;

        // for every line adjust its Y offset based on offset of previous line and X offset based on total width of its glyphs
        for (unsigned int i = beginLineIdx; i < m_vecLines.size(); i++)
        {
            const STextLine& prevLine = m_vecLines[ i - 1 ];
            STextLine& currLine = m_vecLines[i];

            currLineWidth = computeLineWidth( currLine );

            if( !prevLine.vecGlyphs.empty() )
            {
                prevLineHeight = computeLineHeight( prevLine );
            }
            else
            {
                prevLineHeight = initHeight;
            }

            currLine.str = computeLineString( currLine );
            currLine.offset.x = computeLineOffsetX( currLineWidth, maxWidth );
            currLine.offset.y = prevLine.offset.y + prevLineHeight * m_lineSpacing;
        }
    }






    void CText::clear() 
    {
        m_vecRawFragments.clear();
    }

    void CText::append( std::wstring str, EFontStyle styleMask, vec3f color ) 
    {
        STextFragmentRaw fragmRaw;
        fragmRaw.str = str;
        fragmRaw.styleMask = styleMask;
        fragmRaw.color = color;

        m_vecRawFragments.push_back( fragmRaw );
    }

    void CText::append( std::string str, EFontStyle styleMask, vec3f color )
    {
        std::wstring wide = wstringConverter.from_bytes( str );
        append( wide, styleMask, color );
    }

    void CText::newline() 
    {
        append( L"\n" );
    }

    



    std::wstring CText::getString() const
    {
        std::wstring str;
        for( const STextFragmentRaw& fragmRaw : m_vecRawFragments )
        {
            str += fragmRaw.str;
        }

        return str;
    }

    bool CText::isEmpty() const
    {
        return m_vecRawFragments.empty();
    }

    int CText::getWidthPixels() const
    {
        if( !m_resource || m_vecLines.empty() )
        {
            return 0;
        }

        int width, maxWidth = 0;

        for( const STextLine& line : m_vecLines )
        {
            width = computeLineWidth( line );

            if( width > maxWidth )
            {
                maxWidth = width;
            }
        }

        return maxWidth;
    }

    int CText::getHeightPixels() const
    {
        if( !m_resource || m_vecLines.empty() )
        {
            return 0;
        }

        int height;
        const STextLine& lastLine = m_vecLines.back();
        height = lastLine.offset.y + computeLineHeight( lastLine );

        return height;
    }

    vec2i CText::getSizePixels() const
    {
        if( !m_resource || m_vecLines.empty() )
        {
            return { 0, 0 };
        }

        vec2i size;
        size.x = getWidthPixels();
        size.y = getHeightPixels();

        return size;
    }




    void CText::clearData() 
    {
        m_vecLines.clear();
    }

    void CText::generateData() 
    {
        if( !m_resource )
        {
            LOG_WARNING( "Can't generate data for text with invalid font resource!" );
            return;
        }

        m_vecLines.clear();

        for( const STextFragmentRaw& fragmRaw : m_vecRawFragments )
        {
            appendFragment( fragmRaw.str, fragmRaw.styleMask, fragmRaw.color );
        }

        formatLines();
    }

    const std::vector<STextLine>& CText::getData() const
    {
        return m_vecLines;
    }

} // namespace chestnut::engine
