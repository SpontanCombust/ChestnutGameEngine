#include "engine/ecs/component.hpp"

#include "engine/debug/debug.hpp"

namespace engine { namespace ecs {

    void CComponent::setParentEntity(CEntity *entity) 
    {
        if( m_entity != nullptr )
            LOG( "Component already has parent entity!" );

        m_entity = entity;
    }

    CEntity* CComponent::getParentEntity() 
    {
        if( m_entity == nullptr )
            LOG( "Component has no parent entity!" );

        return m_entity;
    }

    const std::string CComponent::getTypeStatic()
    {
        return "";
    }

} /*namespace ecs*/ } // namespace engine 
