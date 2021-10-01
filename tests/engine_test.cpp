#include <catch2/catch.hpp>

#include "../src/chestnut/engine/ecs_impl/system.hpp"
#include "../src/chestnut/engine/main/engine.hpp"

#include <string>


using namespace chestnut::engine;

std::string gstr = "abc";

// just gonna testing the attachSystem variadic template with these systems' various constructors 

class FooSystem : public ISystem
{
public:
    FooSystem( CEngine& engine ) : ISystem( engine ) {}

    void update( float dt ) override
    {
        gstr += 'a';
    }
};

class BarSystem : public ISystem
{
public:
    std::string& strRef;

    BarSystem( CEngine& engine, std::string& str ) : ISystem( engine ), strRef( str ) {}

    void update( float dt ) override
    {
        strRef += 'b';
    }
};

class BazSystem : public ISystem
{
public:
    std::string strA;
    std::string strB;

    BazSystem( CEngine& engine, std::string a, std::string b ) : ISystem( engine )
    {
        strA = a;
        strB = b;
    }

    void update( float dt ) override
    {
        strA += 'c';
        strB += 'd';
    }
};

// this master system will make the engine run for 3 cycles
class MasterSystem : public ISystem
{
public:
    int counter = 0;

    MasterSystem( CEngine& engine ) : ISystem( engine )
    {

    }

    void update( float dt ) override
    {
        counter++;

        if( counter == 3 )
        {
            getEngine().stop();
        }
    }
};


TEST_CASE( "Engine test - handling systems" )
{
    // in this case we won't be doing any rendering, so a working window is not necessary
    std::shared_ptr<CWindow> window;
    CEngine engine( window );

    SECTION( "Constructing, destroying and basic checking" )
    {
        REQUIRE_FALSE( engine.hasSystem<FooSystem>() );
        REQUIRE_FALSE( engine.hasSystem<BarSystem>() );
        REQUIRE_FALSE( engine.hasSystem<BazSystem>() );

        engine.attachLogicSystem<FooSystem>( 1 );
        engine.attachLogicSystem<BarSystem>( 2, gstr );
        engine.attachLogicSystem<BazSystem>( 3, gstr, gstr );
        
        SECTION( "Having systems" )
        {
            REQUIRE( engine.hasSystem<FooSystem>() );
            REQUIRE( engine.hasSystem<BarSystem>() );
            REQUIRE( engine.hasSystem<BazSystem>() );
        }

        SECTION( "Getting systems" )
        {
            FooSystem *foo = engine.getSystem<FooSystem>();
            REQUIRE( foo );

            BarSystem *bar = engine.getSystem<BarSystem>();
            REQUIRE( bar );
            REQUIRE( bar->strRef == gstr );

            BazSystem *baz = engine.getSystem<BazSystem>();
            REQUIRE( baz );
            REQUIRE( baz->strA == gstr );
            REQUIRE( baz->strB == gstr );
        }

        SECTION( "Getting systems' priority numbers" )
        {
            REQUIRE( engine.getSystemPriority<FooSystem>() == 1 );
            REQUIRE( engine.getSystemPriority<BarSystem>() == 2 );
            REQUIRE( engine.getSystemPriority<BazSystem>() == 3 );
        }

        SECTION( "Detaching systems" )
        {
            engine.detachSystem<FooSystem>();
            REQUIRE_FALSE( engine.hasSystem<FooSystem>() );
            REQUIRE( engine.hasSystem<BarSystem>() );
            REQUIRE( engine.hasSystem<BazSystem>() );

            engine.detachSystem<BarSystem>();
            engine.detachSystem<BazSystem>();
            REQUIRE_FALSE( engine.hasSystem<BarSystem>() );
            REQUIRE_FALSE( engine.hasSystem<BazSystem>() );
        }
    }

    SECTION( "Updating systems" )
    {
        SECTION( "Try start without any systems" )
        {
            REQUIRE_THROWS( engine.start() );

            engine.attachLogicSystem<MasterSystem>( SYSTEM_PRIORITY_HIGHEST );
            REQUIRE_NOTHROW( engine.start() );
        }


        engine.attachLogicSystem<MasterSystem>( SYSTEM_PRIORITY_HIGHEST );
        gstr = "";

        SECTION( "foo -> bar -> baz" )
        {
            engine.attachLogicSystem<FooSystem>( 1 );
            engine.attachLogicSystem<BarSystem>( 2, gstr );
            engine.attachLogicSystem<BazSystem>( 3, gstr, gstr );

            engine.start();

            REQUIRE( gstr == "ababab" );
            REQUIRE( engine.getSystem<BazSystem>()->strA == "ccc" );
            REQUIRE( engine.getSystem<BazSystem>()->strB == "ddd" );
        }

        SECTION( "baz -> bar -> foo" )
        {
            engine.attachLogicSystem<FooSystem>( 3 );
            engine.attachLogicSystem<BarSystem>( 2, gstr );
            engine.attachLogicSystem<BazSystem>( 1, gstr, gstr );

            engine.start();

            REQUIRE( gstr == "bababa" );
            REQUIRE( engine.getSystem<BazSystem>()->strA == "ccc" );
            REQUIRE( engine.getSystem<BazSystem>()->strB == "ddd" );
        }
        
        SECTION( "Checking for duplicates" )
        {
            engine.attachLogicSystem<FooSystem>( 3 );
            engine.attachLogicSystem<FooSystem>( 2 );
            engine.attachLogicSystem<BazSystem>( 1, gstr, gstr );

            engine.start();

            REQUIRE( gstr == "aaa" );
            REQUIRE( engine.getSystem<BazSystem>()->strA == "ccc" );
            REQUIRE( engine.getSystem<BazSystem>()->strB == "ddd" );
        }
    }
}
