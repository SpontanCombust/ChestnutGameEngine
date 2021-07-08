namespace chestnut
{
    template<typename C>
    CComponentStorage<C>::CComponentStorage( size_t segmentSize ) : IComponentStorage( segmentSize ) 
    {

    }

    template<typename C>
    CComponentStorage<C>::~CComponentStorage() 
    {
        for( auto& [ segID, segPtr ] : m_mapSegmentIDToSegmentPtr )
        {
            delete segPtr;
            segPtr = nullptr;
        }
    }

    template<typename C>
    CComponentStorageSegment<C>* CComponentStorage<C>::createNewSegment() 
    {
        CComponentStorageSegment<C> *segment;

        m_segmentIDCounter++;
        segment = new CComponentStorageSegment<C>( m_segmentIDCounter, m_segmentSize );

        m_mapSegmentIDToSegmentPtr[ m_segmentIDCounter ] = segment;
        // push back as it's completely empty
        m_dequeAvailableSegments.push_back( segment );

        return segment;
    }

    template<typename C>
    IComponent* CComponentStorage<C>::createComponent( entityid_t entityID ) 
    {
        if( hasComponent( entityID ) )
        {
            return getComponent( entityID );
        }
        
        CComponentStorageSegment<C> *segment;
        if( m_dequeAvailableSegments.empty() )
        {
            // even if new element was pushed back it is at the same time at the "front" as there is only 1 element
            segment = createNewSegment();
        }
        else
        {
            segment = m_dequeAvailableSegments.front();
        }
        
        IComponent *comp = segment->takeUpComponentSlot( entityID );

        m_mapEntityIDToSegmentID[ entityID ] = segment->getID();

        if( !segment->hasFreeComponentSlots() )
        {
            m_dequeAvailableSegments.pop_front();
        }

        return comp;
    }

    template<typename C>
    IComponent* CComponentStorage<C>::getComponent( entityid_t entityID ) const
    {
        auto it = m_mapEntityIDToSegmentID.find( entityID );

        if( it != m_mapEntityIDToSegmentID.end() )
        {
            CComponentStorageSegment<C> *segment = m_mapSegmentIDToSegmentPtr.at( it->second );
            return segment->getSlottedComponent( entityID );
        }
        else
        {
            return nullptr;
        }
    }

    template<typename C>
    bool CComponentStorage<C>::hasComponent( entityid_t entityID ) const 
    {
        if( m_mapEntityIDToSegmentID.find( entityID ) != m_mapEntityIDToSegmentID.end() )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename C>
    void CComponentStorage<C>::eraseComponent( entityid_t entityID ) 
    {
        auto it = m_mapEntityIDToSegmentID.find( entityID );

        if( it != m_mapEntityIDToSegmentID.end() )
        {
            CComponentStorageSegment<C> *segment = m_mapSegmentIDToSegmentPtr.at( it->second );
            segment->freeComponentSlot( entityID );

            m_mapEntityIDToSegmentID.erase( it );

            // if segment was full before and now aquired an empty slot
            if( segment->getFreeComponentSlotCount() == m_segmentSize - 1 )
            {
                // push front as it's got only 1 slot left at this moment
                m_dequeAvailableSegments.push_front( segment );
            }
        }
    }

    template<typename C>
    void CComponentStorage<C>::clearComponents() 
    {
        m_mapEntityIDToSegmentID.clear();

        // clear segments that are on the stack already, so we can push every segment later
        m_dequeAvailableSegments.clear();

        for( auto& [ segID, segPtr ] : m_mapSegmentIDToSegmentPtr )
        {
            segPtr->clearComponentSlots();
            m_dequeAvailableSegments.push_back( segPtr );
        }
    }

    template<typename C>
    void CComponentStorage<C>::reserveComponents( size_t totalSize ) 
    {
        size_t capacity = getComponentCapacity();
        if( totalSize > capacity  )
        {
            reserveMoreComponents( totalSize - capacity );
        }
    }

    template<typename C>
    void CComponentStorage<C>::reserveMoreComponents( size_t additionalSize ) 
    {
        if( additionalSize < m_segmentSize )
        {
            additionalSize = m_segmentSize;
        }

        unsigned int segmentsToCreate;
        unsigned int div, mod;

        div = additionalSize / m_segmentSize;
        mod = additionalSize % m_segmentSize;

        segmentsToCreate = div;
        if( mod > 0 )
        {
            segmentsToCreate++;
        }

        for (unsigned int i = 0; i < segmentsToCreate; i++)
        {
            createNewSegment();
        }
    }

    template<typename C>
    size_t CComponentStorage<C>::getComponentCount() const 
    {
        size_t size = 0;
        for( const auto& [ segID, segPtr ] : m_mapSegmentIDToSegmentPtr )
        {
            size += ( m_segmentSize - segPtr->getFreeComponentSlotCount() );
        }

        return size;
    }

    template<typename C>
    size_t CComponentStorage<C>::getComponentCapacity() const 
    {
        return m_mapSegmentIDToSegmentPtr.size() * m_segmentSize;
    }

    template<typename C>
    unsigned int CComponentStorage<C>::getSegmentCount() const 
    {
        return m_mapSegmentIDToSegmentPtr.size();
    }

    template<typename C>
    unsigned int CComponentStorage<C>::getEmptySegmentCount() const 
    {
        unsigned int emptySegments = 0;

        for( const auto& segPtr : m_dequeAvailableSegments )
        {
            if( segPtr->getFreeComponentSlotCount() == m_segmentSize )
            {
                emptySegments++;
            }
        }

        return emptySegments;
    }

    template<typename C>
    void CComponentStorage<C>::removeEmptySegments() 
    {
        // empty the available segments stack so it won't contain any invalid segments
        // we can readd them later
        m_dequeAvailableSegments.clear();

        CComponentStorageSegment<C> *segPtr;
        size_t freeSlots;
        for( auto it = m_mapSegmentIDToSegmentPtr.begin(); it != m_mapSegmentIDToSegmentPtr.end(); /*NOP*/  )
        {
            segPtr = it->second;
            freeSlots = segPtr->getFreeComponentSlotCount();
            if( freeSlots == m_segmentSize )
            {
                delete segPtr;
                it = m_mapSegmentIDToSegmentPtr.erase(it);
                continue;
            }
            else if( freeSlots > 0 )
            {
                m_dequeAvailableSegments.push_back( segPtr );
            }

            it++;
        }
    }

} // namespace chestnut
