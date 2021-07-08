#include "component_storage.hpp"

namespace chestnut
{    
    IComponentStorage::IComponentStorage( size_t segmentSize ) 
    {
        m_segmentSize = segmentSize;
        m_segmentIDCounter = 0;
    }

    size_t IComponentStorage::getSegmentSize() const
    {
        return m_segmentSize;
    }

} // namespace chestnut
