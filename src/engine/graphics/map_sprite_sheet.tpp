#include "../misc/exception.hpp"

namespace chestnut
{
    template<typename KeyType, typename Compare>
    CMapSpriteSheetTexture2D<KeyType,Compare>::CMapSpriteSheetTexture2D()
    : CTexture2D()
    {

    }

    template<typename KeyType, typename Compare>
    CMapSpriteSheetTexture2D<KeyType,Compare>::CMapSpriteSheetTexture2D( std::shared_ptr<CTexture2DResource> resource )
    : CTexture2D( resource ) 
    {

    }
    
    template<typename KeyType, typename Compare>
    SRectangle CMapSpriteSheetTexture2D<KeyType,Compare>::normalizeRectangle( const SRectangle& rect ) const
    {
        SRectangle normalized;

        int w = m_texResource->width;
        int h = m_texResource->height;

        normalized.x = rect.x / w;
        normalized.y = rect.y / w;
        normalized.w = rect.w / w;
        normalized.h = rect.h / h;

        return normalized;
    }

    template<typename KeyType, typename Compare>
    void CMapSpriteSheetTexture2D<KeyType,Compare>::setSheetFragment( KeyType spriteKey, const SRectangle& rect ) 
    {
        m_mapKeyToClipRect[ spriteKey ] = rect;
    }

    template<typename KeyType, typename Compare>
    void CMapSpriteSheetTexture2D<KeyType,Compare>::setSheetFragments( const std::map< KeyType, SRectangle >& mapKeyToClipRect ) 
    {
        for( auto [ key, rect ] : mapKeyToClipRect )
        {
            m_mapKeyToClipRect[ key ] = rect;
        }
    }

    template<typename KeyType, typename Compare>
    SRectangle CMapSpriteSheetTexture2D<KeyType,Compare>::getSheetFragment( KeyType spriteKey, bool normalize ) const
    {
        auto it = m_mapKeyToClipRect.find( spriteKey );
        auto end = m_mapKeyToClipRect.end();

        if( it == end )
        {
            throw ChestnutException( "Couldn't find sprite sheet fragment key." );
        }
        else
        {
            SRectangle rect = it->second;

            if( normalize )
            {
                rect = normalizeRectangle( rect );
            }

            return rect;
        }
    }

    template<typename KeyType, typename Compare>
    bool CMapSpriteSheetTexture2D<KeyType,Compare>::hasSheetFragment( KeyType spriteKey ) const
    {
        auto it = m_mapKeyToClipRect.find( spriteKey );
        if( it != m_mapKeyToClipRect.end() )
        {
            return true;
        }
        return false;
    }

    template<typename KeyType, typename Compare>
    void CMapSpriteSheetTexture2D<KeyType,Compare>::eraseSheetFragment( KeyType spriteKey ) 
    {
        m_mapKeyToClipRect.erase( spriteKey );
    }

    template<typename KeyType, typename Compare>
    void CMapSpriteSheetTexture2D<KeyType,Compare>::clearSheetFragments() 
    {
        m_mapKeyToClipRect.clear();
    }

    template<typename KeyType, typename Compare>
    void CMapSpriteSheetTexture2D<KeyType,Compare>::setClippingRectUsingSheetFragment( KeyType spriteKey ) 
    {
        auto it = m_mapKeyToClipRect.find( spriteKey );
        if( it != m_mapKeyToClipRect.end() )
        {
            m_clipRect =  *it;
        }
    }

} // namespace chestnut
