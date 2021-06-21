#ifndef __CHESTNUT_MAP_SPRITE_SHEET_H__
#define __CHESTNUT_MAP_SPRITE_SHEET_H__

#include "texture2d.hpp"

#include <map>

namespace chestnut
{
    template< typename KeyType, typename Compare = std::less< KeyType > >
    class CMapSpriteSheetTexture2D : public CTexture2D
    {
    private:
        std::map< KeyType, SRectangle, Compare > m_mapKeyToClipRect;

    public:
        CMapSpriteSheetTexture2D();
        CMapSpriteSheetTexture2D( std::shared_ptr<CTexture2DResource> resource );

        void setFragment( KeyType spriteKey, SRectangle rect, bool normalize );

        // Sets clipping rectanges using already existing map
        // Overwrites elements already existing
        void setFragments( const std::map< KeyType, SRectangle >& mapKeyToClipRect, bool normalize );

        // Throws exception if doesn't find the key
        const SRectangle& getFragment( KeyType spriteKey ) const;

        bool hasFragment( KeyType spriteKey ) const;

        void eraseFragment( KeyType spriteKey );

        void clearFragments();

        void normalizeAllFragments();

        // Sets texture's clipping rectangle as the one established for sprite identified with 'spriteKey'
        // If doesn't find the key, doesn't do anything
        void setClippingRectUsingFragment( KeyType spriteKey );

    private:
        SRectangle normalizeRectangle( const SRectangle& rect );
    };

} // namespace chestnut


#include "map_sprite_sheet.tpp"


#endif // __CHESTNUT_MAP_SPRITE_SHEET_H__