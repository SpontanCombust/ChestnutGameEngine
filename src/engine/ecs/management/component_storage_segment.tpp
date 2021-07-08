#include <numeric>

namespace chestnut
{    
    template<typename C>
    CComponentStorageSegment<C>::CComponentStorageSegment( size_t size ) 
    {
        m_size = size;

        m_arrComponentSlots = new C[ size ];

        m_vecAvailableSlots.resize( size );
        // fill vector with all possible slot numbers
        std::iota( m_vecAvailableSlots.begin(), m_vecAvailableSlots.end(), 0 );
    }

    template<typename C>
    CComponentStorageSegment<C>::~CComponentStorageSegment() 
    {
        delete[] m_arrComponentSlots;
    }

    template<typename C>
    size_t CComponentStorageSegment<C>::getSize() const
    {
        return m_size;
    }

    template<typename C>
    bool CComponentStorageSegment<C>::hasFreeComponentSlots() const
    {
        if( m_vecAvailableSlots.empty() )
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template<typename C>
    size_t CComponentStorageSegment<C>::getFreeComponentSlotCount() const
    {
        return m_vecAvailableSlots.size();
    }

    template<typename C>
    C* CComponentStorageSegment<C>::takeUpComponentSlot( entityid_t entityID ) 
    {
        if( !hasFreeComponentSlots() )
        {
            return nullptr;
        }

        size_t slot = m_vecAvailableSlots.back();
        m_vecAvailableSlots.pop_back();

        // reset component to default state
        m_arrComponentSlots[ slot ] = C();
        m_arrComponentSlots[ slot ].ownerID = entityID;

        m_mapEntityIDToSlot[ entityID ] = slot;

        return &m_arrComponentSlots[ slot ];
    }

    template<typename C>
    bool CComponentStorageSegment<C>::hasSlottedComponent( entityid_t entityID ) const
    {
        if( m_mapEntityIDToSlot.find( entityID ) != m_mapEntityIDToSlot.end() )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename C>
    C* CComponentStorageSegment<C>::getSlottedComponent( entityid_t entityID ) const
    {
        auto it = m_mapEntityIDToSlot.find( entityID );

        if( it != m_mapEntityIDToSlot.end() )
        {
            C *comp = &m_arrComponentSlots[ it->second ];
            return comp;
        }
        else
        {
            return nullptr;
        }
    }

    template<typename C>
    void CComponentStorageSegment<C>::freeComponentSlot( entityid_t entityID ) 
    {
        if( hasSlottedComponent( entityID ) )
        {
            m_mapEntityIDToSlot.erase( entityID );
            m_vecAvailableSlots.push_back( entityID );
        }
    }

    template<typename C>
    void CComponentStorageSegment<C>::clearComponentSlots() 
    {
        m_vecAvailableSlots.clear();
        m_vecAvailableSlots.resize( m_size );
        std::iota( m_vecAvailableSlots.begin(), m_vecAvailableSlots.end(), 0 );

        m_mapEntityIDToSlot.clear();
    }

    template<typename C>
    std::string CComponentStorageSegment<C>::toString() const
    {
        std::string str;

        str += "[";
        if( !m_mapEntityIDToSlot.empty() )
        {
            auto it = m_mapEntityIDToSlot.begin();
            str += std::to_string( it->first );
            it++;

            for(; it != m_mapEntityIDToSlot.end(); it++ )
            {
                str += ", " + std::to_string( it->first );
            }
        }
        str += "]";       

        return str;
    }


} // namespace chestnut
