#include "text.hpp"

#include <algorithm>

namespace chestnut
{    
    CText::CText() 
    {
        m_pointSize = 0;
        m_currentGlyphOffset = 0;
    }

    CText::CText( std::shared_ptr<CFontResource> fontResource, int pointSize ) 
    {
        m_resource = fontResource;
        m_pointSize = pointSize;
        m_currentGlyphOffset = 0;
    }

    bool CText::isValid() const
    {
        if( m_resource && m_resource->isValid() )
        {
            return true;
        }
        return false;
    }

    int CText::getPointSize() const
    {
        return m_pointSize;
    }

    void CText::clear() 
    {
        m_vecFragments.clear();
        m_currentGlyphOffset = {0};
    }

    bool CText::isEmpty() const
    {
        return m_vecFragments.empty();
    }

    std::wstring CText::getString() const
    {
        std::wstring str;
        for( const STextFragment& frag : m_vecFragments )
        {
            str += frag.str;
        }

        return str;
    }

    int CText::getLength() const
    {
        return getString().length();
    }

    void CText::appendString( std::wstring s, EFontStyle style, vec4f color ) 
    {
        const SFontConfig& config = m_resource->getConfig( m_pointSize, style );

        STextFragment fragment;
        fragment.str = s;
        fragment.texID = config.glyphSpriteSheet.getID();
        fragment.color = color;

        for( wchar_t g : s )
        {
            const SGlyphMetrics& metrics = config.mapGlyphMetrics.at(g);
            const SRectangle& clipRect = config.glyphSpriteSheet.getSheetFragment( g, true );

            STextGlyph glyph;
            glyph.g = g;
            glyph.posOffset = m_currentGlyphOffset + vec2f( metrics.xMin, 0 );
            glyph.size = vec2f( metrics.width, metrics.height );
            glyph.uvOffsetNorm = vec2f( clipRect.x, clipRect.y );
            glyph.uvSizeNorm = vec2f( clipRect.w, clipRect.h );

            fragment.vecGlyphs.push_back( glyph );
            
            m_currentGlyphOffset.x() += metrics.advance;
        }

        m_vecFragments.push_back( fragment );
    }

    const std::vector< STextFragment >& CText::getFragments() const
    {
        return m_vecFragments;
    }

} // namespace chestnut
