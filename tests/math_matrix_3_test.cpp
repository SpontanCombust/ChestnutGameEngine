#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/matrix3.hpp"
#include "../src/chestnut/engine/constants.hpp"


using namespace chestnut::engine;

TEST_CASE( "Math - 3-size matrix test" )
{
    SECTION( "Translation matrix" )
    {
        mat3f m = matMakeTranslation<float>( 2.f, 3.f );

        REQUIRE( m(0,0) == Approx(1.f).margin(0.001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,1) == Approx(1.f).margin(0.001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,2) == Approx(2.f).margin(0.001) );
        REQUIRE( m(1,2) == Approx(3.f).margin(0.001) );
        REQUIRE( m(2,2) == Approx(1.f).margin(0.001) );
    }

    SECTION( "Scale matrix" )
    {
        mat3f m = matMakeScale<float>( 2.f, 3.f );

        REQUIRE( m(0,0) == Approx(2.f).margin(0.001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,1) == Approx(3.f).margin(0.001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,2) == Approx(1.f).margin(0.001) );
    }

    SECTION( "Rotation matrix" )
    {
        mat3f m = matMakeRotation<float>( 0.75f * CHESTNUT_PI );

        REQUIRE( m(0,0) == Approx(-0.707f).margin(0.001) );
        REQUIRE( m(1,0) == Approx(0.707f).margin(0.001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,1) == Approx(-0.707f).margin(0.001) );
        REQUIRE( m(1,1) == Approx(-0.707f).margin(0.001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,2) == Approx(1.f).margin(0.001) );
    }
}