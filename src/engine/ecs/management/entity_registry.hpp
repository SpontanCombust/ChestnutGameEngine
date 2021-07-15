#ifndef __CHESTNUT_ENTITY_REGISTRY_H__
#define __CHESTNUT_ENTITY_REGISTRY_H__

#include "entity_signature.hpp"
#include "engine/types.hpp"

#include <utility>
#include <vector>

namespace chestnut
{
    class CEntityRegistry
    {
    private:
        //TODO replace with a map (why TF did I do it like this?!)
        std::vector< std::pair< entityid_t, CEntitySignature > > m_entityRecords;

    public:
        bool addEntity( entityid_t id );

        bool addEntity( entityid_t id, const CEntitySignature& signature );

        void updateEntity( entityid_t id, const CEntitySignature& newSignature );

        bool hasEntity( entityid_t id ) const;

        void removeEntity( entityid_t id );

        void removeAllEntities();

        // Throws exception on not finding the entity
        const CEntitySignature getEntitySignature( entityid_t id ) const;


        const std::string toString() const;
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENTITY_REGISTRY_H__