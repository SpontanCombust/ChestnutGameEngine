#include <catch2/catch.hpp>

#include "../src/engine/ecs/event_manager.hpp"

using namespace chestnut;

struct MyEvent
{
    int i;
};

TEST_CASE( "Event manager test" )
{
    int n1;
    auto l1 = std::make_shared< CEventListener<MyEvent> >( 
        [&n1]( const MyEvent& e ) 
        {
            n1 += e.i;
        }
    );

    int n2;
    auto l2 = std::make_shared< CEventListener<MyEvent> >(
        [&n2]( const MyEvent& e )
        {
            n2 *= e.i;
        },
        []( const MyEvent& e )
        {
            return e.i > 0;
        }
    );

    n1 = 1;
    n2 = 2;
    MyEvent e1{-5}, e2{0}, e3{2};

    CEventManager manager;

    SECTION( "Using simple listener" )
    {
        manager.registerListener( l1 );

        manager.raiseEvent(e1);
        REQUIRE( n1 == -4 );

        manager.raiseEvent(e2);
        REQUIRE( n1 == -4 );

        manager.raiseEvent(e3);
        REQUIRE( n1 == -2 );
    }

    SECTION( "Using listener with filter" )
    {
        manager.registerListener( l2 );

        manager.raiseEvent(e1);
        REQUIRE( n2 == 2 );

        manager.raiseEvent(e2);
        REQUIRE( n2 == 2 );

        manager.raiseEvent(e3);
        REQUIRE( n2 == 4 );
    }

    SECTION( "Unregistering listener" )
    {
        manager.registerListener( l1 );
        manager.registerListener( l2 );

        SECTION( "Before unregistering" )
        {
            manager.raiseEvent(e3);

            REQUIRE( n1 == 3 );
            REQUIRE( n2 == 4 );
        }

        SECTION( "After unregistering" )
        {
            manager.unregisterListener( l1 );

            manager.raiseEvent(e3);
            
            REQUIRE( n1 == 1 );
            REQUIRE( n2 == 4 );
        }
    }
}