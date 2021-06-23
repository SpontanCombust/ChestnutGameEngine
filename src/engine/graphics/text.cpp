#include "text.hpp"

#include "engine/debug/debug.hpp"

#include <algorithm>
#include <codecvt>
#include <locale>

namespace chestnut
{    
    CText::CText() 
    {
        m_pointSize = 0;
        m_positioningMode = ETextPositioningMode::BASELINE;
        m_currentGlyphOffset = { 0, 0 };
    }

    CText::CText( std::shared_ptr<CFontResource> fontResource, int pointSize ) 
    {
        m_resource = fontResource;
        m_pointSize = pointSize;
        m_positioningMode = ETextPositioningMode::BASELINE;
        m_currentGlyphOffset = { 0, 0 };
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



    void CText::setPositioningMode( ETextPositioningMode mode ) 
    {
        m_positioningMode = mode;

        // copy all stored fragments
        std::vector< STextFragment > prevFragments = m_vecFragments;

        // clear them
        clear();

        // reappend them but this time with different positioning
        // because it's easier than writing a lot of conditionals for offset changing
        // based on from which and to which positioning mode we're transitioning
        for( const STextFragment& frag : prevFragments )
        {
            append( frag.str, frag.style, frag.color );
        }
    }

    ETextPositioningMode CText::getPositioningMode() const
    {
        return m_positioningMode;
    }

    void CText::clear() 
    {
        m_vecFragments.clear();
        m_currentGlyphOffset = {0};
    }

    void CText::append( std::wstring s, EFontStyle style, vec4f color ) 
    {
        const SFontConfig& config = m_resource->getConfig( m_pointSize, style );

        STextFragment fragment;
        fragment.str = s;
        fragment.style = style;
        fragment.color = color;
        fragment.texID = config.glyphSpriteSheet.getID();

        bool allGlyphsAvailable = true;
        for( wchar_t g : s )
        {
            SGlyphMetrics metrics;
            SRectangle clipRect;
            if( config.glyphSpriteSheet.hasSheetFragment(g) )
            {
                metrics = config.mapGlyphMetrics.at(g);
                clipRect = config.glyphSpriteSheet.getSheetFragment( g, true );
            }
            else
            {
                // config doesn't have that glyph, have to use some sort of replacement, e.g. a simple space
                metrics = config.mapGlyphMetrics.at( L' ' );
                clipRect = config.glyphSpriteSheet.getSheetFragment( L' ', true );
                allGlyphsAvailable = false;
            }

            STextGlyph glyph;
            glyph.g = g;
            glyph.size = vec2f( metrics.width, metrics.height );
            glyph.uvOffsetNorm = vec2f( clipRect.x, clipRect.y );
            glyph.uvSizeNorm = vec2f( clipRect.w, clipRect.h );

            switch( m_positioningMode )
            {
                case ETextPositioningMode::TOP:
                    glyph.posOffset = m_currentGlyphOffset + vec2f( metrics.xMin, 0 );
                    break;
                case ETextPositioningMode::BASELINE:
                    glyph.posOffset = m_currentGlyphOffset + vec2f( metrics.xMin, -config.ascent );
                    break;
                default: // BOTTOM
                    glyph.posOffset = m_currentGlyphOffset + vec2f( metrics.xMin, -metrics.height );
                    break;
            }
            
            fragment.vecGlyphs.push_back( glyph );
            
            m_currentGlyphOffset.x += metrics.advance;
        }

        if( !allGlyphsAvailable )
        {
            std::wstring_convert< std::codecvt_utf8<wchar_t> > conv;
            LOG_CHANNEL( "TEXT", "Some characters from string \"" << conv.to_bytes(s) << "\" are not available in font " << m_resource->fontPath );
        }

        m_vecFragments.push_back( fragment );
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

    float CText::getWidth() const
    {
        if( isEmpty() )
        {
            return 0.f;
        }

        const STextFragment& lastFrag = m_vecFragments.back();
        const STextGlyph& lastGlyph = lastFrag.vecGlyphs.back();

        // since we always start at zero we just need total offset plus size of the last glyph
        float endPos = lastGlyph.posOffset.x + lastGlyph.size.x;

        return endPos;
    }

    float CText::getHeight() const
    {
        if( isEmpty() )
        {
            return 0.f;
        }

        float maxHeight = 0.f;

        for( const STextFragment& frag : m_vecFragments )
        {
            for( const STextGlyph& glyph : frag.vecGlyphs )
            {
                if( glyph.size.y > maxHeight )
                {
                    maxHeight = glyph.size.y;
                }
            }
        }

        return maxHeight;
    }

    vec2f CText::getSize() const
    {
        if( isEmpty() )
        {
            return { 0.f, 0.f };
        }

        vec2f size = { 0.f, 0.f };

        for( const STextFragment& frag : m_vecFragments )
        {
            for( const STextGlyph& glyph : frag.vecGlyphs )
            {
                size.x = glyph.posOffset.x + glyph.size.x;

                if( glyph.size.y > size.y )
                {
                    size.y = glyph.size.y;
                }
            }
        }

        return size;
    }

    const std::vector< STextFragment >& CText::getFragments() const
    {
        return m_vecFragments;
    }

} // namespace chestnut
