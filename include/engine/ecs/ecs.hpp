#ifndef __CHESTNUT_ECS_H__
#define __CHESTNUT_ECS_H__

#include "component.hpp"
#include "entity.hpp"
#include "component_database.hpp"
#include "component_system.hpp"
#include "components/components.hpp"
#include "component_systems/component_systems.hpp"

#include <vector>
#include <random>

namespace chestnut
{
    class CChestnutECS
    {
    private:
        CComponentDatabase m_componentDB;
        std::vector< IComponentSystem* > m_componentSystems;

        std::vector< guid_t > m_registeredGUIDs;

    public:
        CChestnutECS();
        ~CChestnutECS();

        void onTick();

        bool registerEntity( CEntity *entity, bool generateGUID = true );
        bool pullComponentsFromEntity( CEntity *entity );
        bool registerEntityAndPullComponents( CEntity *entity, bool generateGUID = true );

        const CComponentDatabase& getComponentDatabase() const;

    private:
        bool isEntityRegistered( CEntity *entity );
        void feedComponentSystemsIfNeeded( std::vector< std::type_index >& updatedCompTypes );

    private:
        struct SRandomGUIDGenerator
        {
            std::random_device ranDev;
            std::default_random_engine generator;
            std::uniform_int_distribution< guid_t > distribution;

            SRandomGUIDGenerator()
            {
                generator = std::default_random_engine( ranDev() );
                distribution = std::uniform_int_distribution< guid_t >( 1, 0xFFFFFFFFFFFFFFFF );
            }

            guid_t generate() { return distribution( generator ); }

        } guidGenerator;

    };
    
} // namespace chestnut


#endif // __CHESTNUT_ECS_H__