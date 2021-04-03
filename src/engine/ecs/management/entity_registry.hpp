#ifndef __CHESTNUT_ENTITY_REGISTRY_H__
#define __CHESTNUT_ENTITY_REGISTRY_H__

#include "component_set_signature.hpp"
#include "engine/types.hpp"

#include <utility>
#include <vector>

namespace chestnut
{
    class CEntityRegistry
    {
    private:
        std::vector< std::pair< entityid_t, SComponentSetSignature > > m_entityRecords;

    public:
        bool addEntity( entityid_t id );

        bool addEntity( entityid_t id, const SComponentSetSignature& signature );

        void updateEntity( entityid_t id, const SComponentSetSignature& newSignature );

        void removeEntity( entityid_t id );

        bool hasEntity( entityid_t id ) const;
        // throws exception on not finding the entity
        const SComponentSetSignature getEntitySignature( entityid_t id ) const;
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENTITY_REGISTRY_H__