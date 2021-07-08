#include "ecs_tests.hpp"

#include "engine/ecs/management/component_storage_segment.hpp"
#include "engine/ecs/components/components.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void componentStorageSegmentTest()
    {
        CComponentStorageSegment<STransformComponent> transfCompSegment(0, 5);

        LOG_CHANNEL( "TEST", "<<< Take up slot test >>>" );
        {
            for (int i = 0; i < 6; i++)
            {
                if( transfCompSegment.takeUpComponentSlot( (entityid_t)i ) )
                {
                    LOG_CHANNEL( "TEST", "Entity " << i << " took up a segment slot." );
                }
                else
                {
                    LOG_CHANNEL( "TEST", "Segment ran out of space!" );
                }
            }
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<< has-get slot test >>>" );
        {
            if( !transfCompSegment.hasFreeComponentSlots() )
            {
                LOG_CHANNEL( "TEST", "Segment is full!" );
            }
            else
            {
                LOG_CHANNEL( "TEST", "[ERROR] Segment has some free space!" );
            }

            if( transfCompSegment.hasSlottedComponent(4) )
            {
                LOG_CHANNEL( "TEST", "Segment has slotted entity 4!" );
            }
            else
            {
                LOG_CHANNEL( "TEST", "[ERROR] Segment doesn't have entity 4!" );
            }

            if( transfCompSegment.hasSlottedComponent(5) )
            {
                LOG_CHANNEL( "TEST", "[ERROR] Segment has slotted entity 5!" );
            }
            else
            {
                LOG_CHANNEL( "TEST", "Segment doesn't have entity 5!" );
            }

            STransformComponent *comp = transfCompSegment.getSlottedComponent(4);
            if( comp )
            {
                LOG_CHANNEL( "TEST", "Entity under id=4 exists. Inner id=" << comp->ownerID );
            }
            else
            {
                LOG_CHANNEL( "TEST", "[ERROR] Segment doesn't have entity under id=4!" );
            }
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<< free slot test >>>" );
        {
            transfCompSegment.freeComponentSlot(0);

            if( transfCompSegment.hasSlottedComponent(0) )
            {
                LOG_CHANNEL( "TEST", "[ERROR] Segment has slotted entity 0!" );
            }
            else
            {
                LOG_CHANNEL( "TEST", "Segment doesn't have entity 0!" );
            }

            LOG_CHANNEL( "TEST", "Free slot count: " << transfCompSegment.getFreeComponentSlotCount() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<< toString test >>>" );
        {
            LOG_CHANNEL( "TEST", transfCompSegment.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<< clear-take up test >>>" );
        {
            transfCompSegment.clearComponentSlots();

            LOG_CHANNEL( "TEST", "Free slot count: " << transfCompSegment.getFreeComponentSlotCount() );

            transfCompSegment.takeUpComponentSlot(0);

            LOG_CHANNEL( "TEST", "Free slot count: " << transfCompSegment.getFreeComponentSlotCount() );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut
