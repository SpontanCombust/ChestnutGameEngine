#include <catch2/catch.hpp>

#include "../src/engine/ecs/event_listener.hpp"


using namespace chestnut;

struct SNumSwitchEvent
{
    int val;
};

int testNum;

event_function pureFunc( const SNumSwitchEvent& e )
{
    testNum += e.val;
}

class Foo
{
public:
    event_function membFunc( const SNumSwitchEvent& e )
    {
        testNum -= e.val;
    }
};

auto lambdaFunc = []( const SNumSwitchEvent& e ) -> event_function
{
    testNum *= e.val;   
};

auto filter = []( const SNumSwitchEvent& e ) -> bool
{
    return e.val > 0;
};


TEST_CASE( "Event listener test" )
{
    SECTION( "Is enabled by default and has appropriate event type stored" )
    {
        CEventListener<SNumSwitchEvent> l1, l2( lambdaFunc ), l3( lambdaFunc, filter );

        REQUIRE( l1.isEnabled() );
        REQUIRE( l2.isEnabled() );
        REQUIRE( l3.isEnabled() );

        REQUIRE( l1.m_eventType == typeid(SNumSwitchEvent) );
        REQUIRE( l2.m_eventType == typeid(SNumSwitchEvent) );
        REQUIRE( l3.m_eventType == typeid(SNumSwitchEvent) );
    }

    SECTION( "Pure function handler" )
    {
        CEventListener<SNumSwitchEvent> listener;

        listener.setHandler( pureFunc );

        testNum = 0;

        SNumSwitchEvent e;
        e.val = 5;
        listener.invokeHandler(e);
        e.val = 2;
        listener.invokeHandler(e);

        REQUIRE( testNum == 7 );
    }

    SECTION( "Member function handler" )
    {
        CEventListener<SNumSwitchEvent> listener;
        Foo foo;
        
        listener.setHandler( &Foo::membFunc, &foo );

        testNum = 0;

        SNumSwitchEvent e;
        e.val = 2;
        listener.invokeHandler(e);
        
        REQUIRE( testNum == -2 );
    }

    SECTION( "Lambda function handler" )
    {
        CEventListener<SNumSwitchEvent> listener;

        listener.setHandler( lambdaFunc );

        testNum = 0;

        SNumSwitchEvent e;
        testNum = 1;
        e.val = 10;
        listener.invokeHandler(e);

        REQUIRE( testNum == 10 );
    }

    SECTION( "Default listener filter" )
    {
        CEventListener<SNumSwitchEvent> l1, l2( lambdaFunc );

        SNumSwitchEvent e { -1 };

        REQUIRE( l1.testFilter(e) );
        REQUIRE( l2.testFilter(e) );
    }

    SECTION( "Filtering events" )
    {
        CEventListener<SNumSwitchEvent> listener;

        listener.setFilter( filter );

        SNumSwitchEvent e1{-1}, e2{0}, e3{1};

        REQUIRE_FALSE( listener.testFilter(e1) );
        REQUIRE_FALSE( listener.testFilter(e2) );
        REQUIRE( listener.testFilter(e3) );
    }

    SECTION( "Filtering and invoking only for accepted events" )
    {
        CEventListener<SNumSwitchEvent> listener;

        listener.setHandler( pureFunc );
        listener.setFilter( filter );

        testNum = 0;

        SNumSwitchEvent e1{1}, e2{-2}, e3{3};

        listener.invokeHandlerIfFilterAccepts(e1);
        REQUIRE( testNum == 1 );
        listener.invokeHandlerIfFilterAccepts(e2);
        REQUIRE( testNum == 1 );
        listener.invokeHandlerIfFilterAccepts(e3);
        REQUIRE( testNum == 4 );
    }
}