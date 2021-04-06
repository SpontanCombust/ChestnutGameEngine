#ifndef __CHESTNUT_COMPONENT_BATCH_H__
#define __CHESTNUT_COMPONENT_BATCH_H__

#include "component_set_signature.hpp"
#include "component_set.hpp"
#include "engine/ecs/component.hpp"
#include "engine/types.hpp"

#include <unordered_map>
#include <vector>

namespace chestnut
{
    /**
     * @brief A struct-of-arrays class containing component pointers belonging to multiple entities having the same component signature
     * 
     * @details
     * A class housing parallel arrays (vectors) of component pointers. A batch is created for a specified component set signature. 
     * A class created from need of storing unspecified number of components of unspecified number of types. 
     * Allows for convenient access to components that belong to an entity with specific set of components, 
     * which streamlines component systems' process of fetching very specific component configurations if they need more than one 
     * type to perform an operation (for example transform component is needed for a renderable component to be drawn at a specific location). 
     * You may submit component by passing a component set with corresponding signature. 
     * You may get component pointers in form of a vector for specified component type. 
     */
    class CComponentBatch
    {
    private:
        SComponentSetSignature m_signature;
        
        std::vector< entityid_t > m_entityIDs;
        std::unordered_map< std::type_index, std::vector<IComponent *> > m_mapTindexToCompVec;

    public:
        CComponentBatch() = default;

        CComponentBatch( const SComponentSetSignature& signature );

        ~CComponentBatch();


        void setSignature( const SComponentSetSignature& signature );

        const SComponentSetSignature& getSignature() const;

        const int getEntityCount() const;

        const std::vector< entityid_t >& getEntities() const;

        template< typename T >
        std::vector< T * > getComponents();

        bool submitComponentSet( const SComponentSet& compSet );

        void removeComponentSet( entityid_t id );

        void removeAllComponentSets();


        const std::string toString() const;
    };
    
} // namespace chestnut


#include "component_batch.tpp"


#endif // __CHESTNUT_COMPONENT_BATCH_H__