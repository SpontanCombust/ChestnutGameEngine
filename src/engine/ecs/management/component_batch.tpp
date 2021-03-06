#include "engine/debug/debug.hpp"

namespace chestnut
{
    template< typename T >
    std::vector<IComponent*> CComponentBatch::getComponentsRaw() const
    {
        if( m_signature.includes<T>() )
        {
            return m_mapTindexToCompVec.at( TINDEX(T) );
        }
        else
        {
            LOG_CHANNEL( "COMPONENT_BATCH", "Tried fetching a component type that is not stored in the batch!" );
            LOG_CHANNEL( "COMPONENT_BATCH", "This batch's signature is: " + m_signature.toString() );
            LOG_CHANNEL( "COMPONENT_BATCH", "Tried fetching component type: " << TINDEX_NAME(T) );
            return std::vector<IComponent*>(); //return empty vector
        }
    }

    template< typename T >
    std::vector< T * > CComponentBatch::getComponents() const
    {
        std::vector< T * > typedCompVec;

        if( m_signature.includes<T>() )
        {
            std::vector< IComponent * > untypedCompVec;

            untypedCompVec = m_mapTindexToCompVec.at( TINDEX(T) );

            T *typedComp;
            for( IComponent *untypedComp : untypedCompVec )
            {
                typedComp = dynamic_cast< T * >( untypedComp );
                typedCompVec.push_back( typedComp );
            }
        }
        else
        {
            LOG_CHANNEL( "COMPONENT_BATCH", "Tried fetching a component type that is not stored in the batch!" );
            LOG_CHANNEL( "COMPONENT_BATCH", "This batch's signature is: " + m_signature.toString() );
            LOG_CHANNEL( "COMPONENT_BATCH", "Tried fetching component type: " << TINDEX_NAME(T) );
        }
        

        // if a batch doesn't have that component type, return empty vector
        return typedCompVec;
    }

    template< typename T >
    void CComponentBatch::getComponentsAppendToVec( std::vector<T*>& vec ) const
    {
        if( m_signature.includes<T>() )
        {
            std::vector< IComponent * > untypedCompVec;
            untypedCompVec = m_mapTindexToCompVec.at( TINDEX(T) );

            vec.reserve( vec.capacity() + untypedCompVec.size() );

            T *typedComp;
            for( IComponent *untypedComp : untypedCompVec )
            {
                typedComp = dynamic_cast< T * >( untypedComp );
                vec.push_back( typedComp );
            }
        }
        else
        {
            LOG_CHANNEL( "COMPONENT_BATCH", "Tried fetching a component type that is not stored in the batch!" );
            LOG_CHANNEL( "COMPONENT_BATCH", "This batch's signature is: " + m_signature.toString() );
            LOG_CHANNEL( "COMPONENT_BATCH", "Tried fetching component type: " << TINDEX_NAME(T) );
        }
    }

} // namespace chestnut
