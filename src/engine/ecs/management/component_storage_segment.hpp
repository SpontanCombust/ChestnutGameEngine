#ifndef __CHESTNUT_COMPONENT_STORAGE_SEGMENT_H__
#define __CHESTNUT_COMPONENT_STORAGE_SEGMENT_H__

#include "engine/types.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace chestnut
{
    template< typename C >
    class CComponentStorageSegment
    {
    private:
        size_t m_size;
        C *m_arrComponentSlots;

        std::vector< size_t > m_vecAvailableSlots;
        std::unordered_map< entityid_t, size_t > m_mapEntityIDToSlot;

    public:
        CComponentStorageSegment( size_t size );
        ~CComponentStorageSegment();

        size_t getSize() const;

        bool hasFreeComponentSlots() const;
        
        size_t getFreeComponentSlotCount() const;

        // Returns null if no slots are available
        C *takeUpComponentSlot( entityid_t entityID );

        bool hasSlottedComponent( entityid_t entityID ) const;

        // Returns null if there is not slot for given entity
        C* getSlottedComponent( entityid_t entityID ) const;

        void freeComponentSlot( entityid_t entityID );

        void clearComponentSlots();
        // Returns a string with IDs of all entities that take up a slot in the segment
        std::string toString() const;

    private:

    };

} // namespace chestnut


#include "component_storage_segment.tpp"


#endif // __CHESTNUT_COMPONENT_STORAGE_SEGMENT_H__