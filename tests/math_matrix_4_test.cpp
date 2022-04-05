#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/matrix4.hpp"
#include "../src/chestnut/engine/constants.hpp"


using namespace chestnut::engine;

TEST_CASE( "Math - 4-size matrix test" )
{
    SECTION( "Orthographic matrix" )
    {
        mat4f m = matMakeOrthographic<float>( -20.f, 30.f, 10.f, 50.f, 15.f, -25.f );

        REQUIRE( m(0,0) == Approx(0.04f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(0.05f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(0.05f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(-0.2f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(-1.5f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(-0.25f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.00001) );
    }

    SECTION( "Frustum matrix" )
    {
        mat4f m = matMakeFrustum<float>( -30.f, 30.f, -20.f, 20.f, 1.f, 1000.f );

        REQUIRE( m(0,0) == Approx(0.03333f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(0.05f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(-1.002002f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(-1.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(-2.002002f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(0.f).margin(0.00001) );
    }

    SECTION( "Perspective matrix" )
    {
        mat4f m = matMakePerspective<float>( 10.f, 20.f, 30.f, 40.f );

        REQUIRE( m(0,0) == Approx(-0.0147906f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(-0.2958129f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(-7.f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(-1.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(-240.f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(0.f).margin(0.00001) );
    }

    SECTION( "Look-at matrix" )
    {
        //TODO Look-at matrix test
    }

    SECTION( "Translation matrix" )
    {
        mat4f m = matMakeTranslation<float>( 2.f, 3.f, 4.f );

        REQUIRE( m(0,0) == Approx(1.0f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(1.f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(1.f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(2.f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(3.f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(4.f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.00001) );
    }

    SECTION( "Scale matrix" )
    {
        mat4f m = matMakeScale<float>( 2.f, 3.f, 4.f );

        REQUIRE( m(0,0) == Approx(2.0f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(3.f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(4.f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.00001) );
    }

    SECTION( "X-rotation matrix" )
    {
        mat4f m = matMakeRotationX<float>( 0.75 * CHESTNUT_PI );

        REQUIRE( m(0,0) == Approx(1.0f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(-0.70710678f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.70710678f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(-0.70710678f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(-0.70710678f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.00001) );
    }

    SECTION( "Y-rotation matrix" )
    {
        mat4f m = matMakeRotationY<float>( CHESTNUT_PI );

        REQUIRE( m(0,0) == Approx(-1.0f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(1.f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(-1.f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.00001) );
    }

    SECTION( "Z-rotation matrix" )
    {
        mat4f m = matMakeRotationZ<float>( 0.5 * CHESTNUT_PI );

        REQUIRE( m(0,0) == Approx(0.0f).margin(0.00001) );
        REQUIRE( m(1,0) == Approx(1.f).margin(0.00001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,1) == Approx(-1.f).margin(0.00001) );
        REQUIRE( m(1,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,2) == Approx(1.f).margin(0.00001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.00001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(2,3) == Approx(0.f).margin(0.00001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.00001) );
    }

    SECTION( "Axis-rotation matrix" )
    {
        //TODO Axis-rotation matrix test
    }
}