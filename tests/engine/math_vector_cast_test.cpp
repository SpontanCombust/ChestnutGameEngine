#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/vector_cast.hpp"
#include "../src/chestnut/engine/maths/vector2.hpp"
#include "../src/chestnut/engine/maths/vector3.hpp"


using namespace chestnut::engine;

TEST_CASE( "Math - Vector casting test" )
{
    SECTION( "Casting to greater size specifically" )
    {
        vec2f v1 { 1.f, 2.f };

        vec3f v2 = vecCastSizeGreater<3>( v1, 3.f );

        REQUIRE( v2.x == Approx(1.0).margin(0.001) );
        REQUIRE( v2.y == Approx(2.0).margin(0.001) );
        REQUIRE( v2.z == Approx(3.0).margin(0.001) );
    }

    SECTION( "Casting to smaller size specifically" )
    {
        vec3f v1 { 1.f, 2.f, 3.f };

        vec2f v2 = vecCastSizeSmaller<2>( v1 );

        REQUIRE( v2.x == Approx(1.0).margin(0.001) );
        REQUIRE( v2.y == Approx(2.0).margin(0.001) );
    }

    SECTION( "Casting to other size with the same generic function" )
    {
        vec2f v1 { 1.f, 2.f };

        vec3f v2 = vecCastSize<3>( v1, 3.f );

        REQUIRE( v2.x == Approx(1.0).margin(0.001) );
        REQUIRE( v2.y == Approx(2.0).margin(0.001) );
        REQUIRE( v2.z == Approx(3.0).margin(0.001) );


        vec3f v3 { 1.f, 2.f, 3.f };

        vec2f v4 = vecCastSize<2>( v3 );

        REQUIRE( v4.x == Approx(1.0).margin(0.001) );
        REQUIRE( v4.y == Approx(2.0).margin(0.001) );
    }

    SECTION( "Casting to vector with different underlying type" )
    {
        vec2f v1 { 2.f, -1.5f };

        vec2i v2 = vecCastType<int>( v1 );

        REQUIRE( v2.x == 2 );
        REQUIRE( v2.y == -1 );
    }

    SECTION( "Casting to vector with different size and underlying type" )
    {
        vec2f v1 { 1.f, -1.5f };

        Vector<int,3> v2 = vecCast<int,3>( v1, 2 );

        REQUIRE( v2.x == 1 );
        REQUIRE( v2.y == -1 );
        REQUIRE( v2.z == 2 );
    }
}