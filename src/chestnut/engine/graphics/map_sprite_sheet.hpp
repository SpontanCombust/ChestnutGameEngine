#ifndef __CHESTNUT_ENGINE_MAP_SPRITE_SHEET_H__
#define __CHESTNUT_ENGINE_MAP_SPRITE_SHEET_H__

#include "texture2d.hpp"

#include <map>

namespace chestnut::engine
{
    template< typename KeyType, typename Compare = std::less< KeyType > >
    class CMapSpriteSheetTexture2D : public CTexture2D
    {
    private:
        // Coordinates and dimensions of rectangles in pixels
        std::map< KeyType, SRectangle, Compare > m_mapKeyToClipRect;

    public:
        CMapSpriteSheetTexture2D();
        CMapSpriteSheetTexture2D( std::shared_ptr<CTexture2DResource> resource );

        // Coordinates and dimensions of rectangle in pixels
        void setSheetFragment( KeyType spriteKey, const SRectangle& rect );

        // Sets clipping rectanges using already existing map
        // Overwrites elements already existing
        // Coordinates and dimensions of rectangles in pixels
        void setSheetFragments( const std::map< KeyType, SRectangle >& mapKeyToClipRect );

        // Throws exception if doesn't find the key
        // Rectangle metrics eighter in pixels or normalized when normalize=true
        SRectangle getSheetFragment( KeyType spriteKey, bool normalize ) const;

        bool hasSheetFragment( KeyType spriteKey ) const;

        void eraseSheetFragment( KeyType spriteKey );

        void clearSheetFragments();

        // Sets texture's clipping rectangle as the one established for sprite identified with 'spriteKey'
        // If doesn't find the key, doesn't do anything
        void setClippingRectUsingSheetFragment( KeyType spriteKey );

    private:
        SRectangle normalizeRectangle( const SRectangle& rect ) const;
    };

} // namespace chestnut::engine


#include "map_sprite_sheet.tpp"


#endif // __CHESTNUT_ENGINE_MAP_SPRITE_SHEET_H__