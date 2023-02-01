#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"
#include "../src/chestnut/engine/main/engine.hpp"
#include "../src/chestnut/engine/ecs_impl/system.hpp"

#include <string>


using namespace chestnut::engine;

std::string gstr = "abc";

// just gonna testing the attachSystem variadic template with these systems' various constructors 

class FooSystem : public ILogicSystem
{
public:
    FooSystem(systempriority_t priority) : ILogicSystem(priority) {}

    void update( float dt ) override
    {
        gstr += 'a';
    }
};

class BarSystem : public ILogicSystem
{
public:
    std::string& strRef;

    BarSystem( systempriority_t priority, std::string& str ) : ILogicSystem(priority), strRef( str ) {}

    void update( float dt ) override
    {
        strRef += 'b';
    }
};

class BazSystem : public ILogicSystem
{
public:
    std::string strA;
    std::string strB;

    BazSystem( systempriority_t priority, std::string a, std::string b ) : ILogicSystem( priority )
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
class MasterSystem : public ILogicSystem
{
public:
    int counter = 0;

    MasterSystem(systempriority_t priority) : ILogicSystem(priority)
    {

    }

    void update( float dt ) override
    {
        counter++;

        if( counter == 3 )
        {
            CEngine::getInstance().stop();
        }
    }
};


TEST_CASE( "Engine - Handling systems" )
{
    chestnutInit();

    // in this case we won't be doing any rendering, so a working window is not necessary
    CWindow window("", 800, 600, EWindowDisplayMode::WINDOWED, -1, -1, false);
    CEngine::createInstance(window);

    auto& engine = CEngine::getInstance(); 

    auto foo = new FooSystem(1);
    auto bar = new BarSystem(2, gstr);
    auto baz = new BazSystem(3, gstr, gstr);
    auto master = new MasterSystem(SYSTEM_PRIORITY_HIGHEST);

    SECTION( "Constructing, destroying and basic checking" )
    {
        REQUIRE( engine.getLogicSystem<FooSystem>() == nullptr );
        REQUIRE( engine.getLogicSystem<BarSystem>() == nullptr );
        REQUIRE( engine.getLogicSystem<BazSystem>() == nullptr );

        engine.attachSystem(foo);
        engine.attachSystem(bar);
        engine.attachSystem(baz);
        
        SECTION( "Having systems" )
        {
            REQUIRE( engine.getLogicSystem<FooSystem>() != nullptr );
            REQUIRE( engine.getLogicSystem<BarSystem>() != nullptr );
            REQUIRE( engine.getLogicSystem<BazSystem>() != nullptr );
        }

        SECTION( "Getting systems" )
        {
            FooSystem *_foo = engine.getLogicSystem<FooSystem>();
            REQUIRE( _foo == foo );

            BarSystem *_bar = engine.getLogicSystem<BarSystem>();
            REQUIRE( _bar == bar );
            REQUIRE( _bar->strRef == gstr );

            BazSystem *_baz = engine.getLogicSystem<BazSystem>();
            REQUIRE( _baz == baz );
            REQUIRE( _baz->strA == gstr );
            REQUIRE( _baz->strB == gstr );
        }

        SECTION( "Getting systems' priority numbers" )
        {
            REQUIRE( engine.getLogicSystem<FooSystem>()->getPriority() == 1 );
            REQUIRE( engine.getLogicSystem<BarSystem>()->getPriority() == 2 );
            REQUIRE( engine.getLogicSystem<BazSystem>()->getPriority() == 3 );
        }

        SECTION( "Detaching systems" )
        {
            engine.detachSystem(foo);
            REQUIRE( engine.getLogicSystem<FooSystem>() == nullptr );
            REQUIRE( engine.getLogicSystem<BarSystem>() != nullptr );
            REQUIRE( engine.getLogicSystem<BazSystem>() != nullptr );

            engine.detachSystem(bar);
            engine.detachSystem(baz);
            REQUIRE( engine.getLogicSystem<BarSystem>() == nullptr );
            REQUIRE( engine.getLogicSystem<BazSystem>() == nullptr );
        }
    }

    SECTION( "Updating systems" )
    {
        SECTION( "Try start without any systems" )
        {
            REQUIRE_THROWS( engine.start() );

            engine.attachSystem(master);
            REQUIRE_NOTHROW( engine.start() );
        }


        gstr = "";
        baz->strA = "";
        baz->strB = "";

        engine.attachSystem(master);
        engine.attachSystem(foo);
        engine.attachSystem(bar);
        engine.attachSystem(baz);

        SECTION( "foo -> bar -> baz" )
        {
            foo->setPriority(1);
            bar->setPriority(2);
            baz->setPriority(3);

            engine.reorderSystems();
            engine.start();

            REQUIRE( gstr == "ababab" );
            REQUIRE( baz->strA == "ccc" );
            REQUIRE( baz->strB == "ddd" );
        }

        SECTION( "baz -> bar -> foo" )
        {
            foo->setPriority(3);
            bar->setPriority(2);
            baz->setPriority(1);

            engine.reorderSystems();
            engine.start();

            REQUIRE( gstr == "bababa" );
            REQUIRE( baz->strA == "ccc" );
            REQUIRE( baz->strB == "ddd" );
        }
    }

    CEngine::deleteInstance();
    chestnutQuit();
}
