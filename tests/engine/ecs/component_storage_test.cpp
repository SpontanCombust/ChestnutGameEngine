#include "ecs_tests.hpp"

#include "engine/debug/debug.hpp"
#include "engine/ecs/management/component_storage.hpp"

namespace chestnut
{
namespace test
{
    void componentStorageTest()
    {
        IComponentStorage *storage = new CComponentStorage< IComponent >(10);

        LOG_CHANNEL( "TEST", "<<< create-has-get test >>>" );
        {
            LOG_CHANNEL( "TEST", "Erased components of entites 20 and 19" );
            for (size_t i = 0; i < 20; i++)
            {
                storage->createComponent(i);   
            }

            LOG_ASSERT( "Has component from entity=11", storage->hasComponent(11) );

            LOG_ASSERT( "Has component for entity=11 is valid", storage->getComponent(11)->ownerID == 11 );

            LOG_ASSERT( "Doesn't have component from entity=21", !storage->hasComponent(21) );


            LOG_CHANNEL( "TEST", "Component count: " << storage->getComponentCount() );
            LOG_CHANNEL( "TEST", "Component capacity: " << storage->getComponentCapacity() );
            LOG_CHANNEL( "TEST", "Segment count: " << storage->getSegmentCount() );
        }
        LOG_CHANNEL( "TEST", "" );
        

        LOG_CHANNEL( "TEST", "<<< erase test >>>" );
        {
            storage->eraseComponent(20);
            storage->eraseComponent(19);
            LOG_CHANNEL( "TEST", "Erased components of entites 20 and 19" );

            LOG_ASSERT( "Doesn't have component from entity=20", !storage->hasComponent(20) );

            LOG_CHANNEL( "TEST", "Component count: " << storage->getComponentCount() );
            LOG_CHANNEL( "TEST", "Component capacity: " << storage->getComponentCapacity() );
            LOG_CHANNEL( "TEST", "Segment count: " << storage->getSegmentCount() );
            LOG_CHANNEL( "TEST", "Empty segment count: " << storage->getEmptySegmentCount() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<< reserve-remove empty test >>>" );
        {
            storage->reserveMoreComponents(9);
            LOG_CHANNEL( "TEST", "Reserved 9 more" );

            LOG_CHANNEL( "TEST", "Component capacity: " << storage->getComponentCapacity() );
            LOG_CHANNEL( "TEST", "Segment count: " << storage->getSegmentCount() );
            LOG_CHANNEL( "TEST", "Empty segment count: " << storage->getEmptySegmentCount() );

            storage->reserveComponents(41);
            LOG_CHANNEL( "TEST", "Reserved 41 total" );

            LOG_CHANNEL( "TEST", "Component capacity: " << storage->getComponentCapacity() );
            LOG_CHANNEL( "TEST", "Segment count: " << storage->getSegmentCount() );
            LOG_CHANNEL( "TEST", "Empty segment count: " << storage->getEmptySegmentCount() );

            storage->removeEmptySegments();
            LOG_CHANNEL( "TEST", "Removed empty segments" );

            LOG_CHANNEL( "TEST", "Component capacity: " << storage->getComponentCapacity() );
            LOG_CHANNEL( "TEST", "Segment count: " << storage->getSegmentCount() );
            LOG_CHANNEL( "TEST", "Empty segment count: " << storage->getEmptySegmentCount() );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut
