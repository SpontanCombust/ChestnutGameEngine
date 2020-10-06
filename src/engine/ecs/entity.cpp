#include "engine/ecs/entity.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    guid_t CEntity::getGUID() const
    {
        return m_GUID;
    }

    bool CEntity::addComponent( IComponent *component ) 
    {
        if( component == nullptr )
            return false;

        std::type_index tindex = std::type_index( typeid( *component ) );
        if( m_components.find(tindex) != m_components.end() )
        {
            LOG( "Entity " + std::to_string(m_GUID) + " already has component: " << typeid(*component).name() );
            return false;
        }
        
        m_components[tindex] = component;
        return true;
    }

    const std::vector< std::type_index > CEntity::getComponentTypeIndexes() const
    {
        std::vector< std::type_index > indexes;
        std::type_index tindex = std::type_index( typeid(IComponent) );
        for( const auto &pair : m_components )
        {
            tindex = pair.first;
            indexes.push_back( tindex );
        }

        return indexes;
    }

} // namespace chestnut 