#include <catch2/catch.hpp>

#include "../src/engine/ecs/event_manager.hpp"

using namespace chestnut;

struct MyEvent
{
    int i;
};

TEST_CASE( "Event manager test" )
{
    int n1 = 1;
    auto l1 = std::make_shared< CEventListener<MyEvent> >( 
        [&n1]( const MyEvent& e ) 
        {
            n1 += e.i;
        }
    );

    int n2 = 1;
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

    MyEvent e1{-5}, e2{0}, e3{2};

    CEventManager manager;

    manager.registerListener( l1 );
    manager.registerListener( l2 );

    manager.raiseEvent(e1);
    REQUIRE( n1 == -4 );
    REQUIRE( n2 == 1 );

    manager.raiseEvent(e2);
    REQUIRE( n1 == -4 );
    REQUIRE( n2 == 1 );

    manager.raiseEvent(e3);
    REQUIRE( n1 == -2 );
    REQUIRE( n2 == 2 );
}