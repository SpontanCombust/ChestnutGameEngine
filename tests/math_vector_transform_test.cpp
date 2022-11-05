#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/vector_transform.hpp"
#include "../src/chestnut/engine/constants.hpp"


using namespace chestnut::engine;

TEST_CASE( "Math - Vector transformation test" )
{
    SECTION( "vec2 transform" )
    {
        vec2f v { 2.f, 3.f };

        SECTION( "Translation by matrix" )
        {
            mat3f m = matMakeTranslation<float>( 4.f, 5.f );

            v = m * v;

            REQUIRE( v.x == Approx(6.f).margin(0.001) );
            REQUIRE( v.y == Approx(8.f).margin(0.001) );
        }

        SECTION( "Translation by function" )
        {
            vecTranslate( v, 4.f, 5.f );

            REQUIRE( v.x == Approx(6.f).margin(0.001) );
            REQUIRE( v.y == Approx(8.f).margin(0.001) );
        }

        SECTION( "Scale by matrix" )
        {
            mat3f m = matMakeScale<float>( 4.f, 5.f );

            v = m * v;

            REQUIRE( v.x == Approx(8.f).margin(0.001) );
            REQUIRE( v.y == Approx(15.f).margin(0.001) );
        }

        SECTION( "Scale by function" )
        {
            vecScale( v, 4.f, 5.f );

            REQUIRE( v.x == Approx(8.f).margin(0.001) );
            REQUIRE( v.y == Approx(15.f).margin(0.001) );
        }

        SECTION( "Rotation by matrix" )
        {
            mat3f m = matMakeRotation<float>( CHESTNUT_PI_F );

            v = m * v;

            REQUIRE( v.x == Approx(-2.f).margin(0.001) );
            REQUIRE( v.y == Approx(-3.f).margin(0.001) );
        }

        SECTION( "Rotation by function" )
        {
            vecRotate( v, CHESTNUT_PI_F );

            REQUIRE( v.x == Approx(-2.f).margin(0.001) );
            REQUIRE( v.y == Approx(-3.f).margin(0.001) );
        }
    }

    SECTION( "vec3 transform" )
    {
        vec3f v = { 1.f, 2.f, 3.f };

        SECTION( "Translation by matrix" )
        {
            mat4f m  = matMakeTranslation<float>( 4.f, 5.f, 6.f );

            v = m * v;

            REQUIRE( v.x == Approx(5.f).margin(0.001) );
            REQUIRE( v.y == Approx(7.f).margin(0.001) );
            REQUIRE( v.z == Approx(9.f).margin(0.001) );
        }

        SECTION( "Translation by function" )
        {
            vecTranslate( v, 4.f, 5.f, 6.f );

            REQUIRE( v.x == Approx(5.f).margin(0.001) );
            REQUIRE( v.y == Approx(7.f).margin(0.001) );
            REQUIRE( v.z == Approx(9.f).margin(0.001) );
        }

        SECTION( "Scale by matrix" )
        {
            mat4f m = matMakeScale<float>( 4.f, 5.f, 6.f );

            v = m * v;

            REQUIRE( v.x == Approx(4.f).margin(0.001) );
            REQUIRE( v.y == Approx(10.f).margin(0.001) );
            REQUIRE( v.z == Approx(18.f).margin(0.001) );
        }

        SECTION( "Scale by function" )
        {
            vecScale( v, 4.f, 5.f, 6.f );

            REQUIRE( v.x == Approx(4.f).margin(0.001) );
            REQUIRE( v.y == Approx(10.f).margin(0.001) );
            REQUIRE( v.z == Approx(18.f).margin(0.001) );
        }

        SECTION( "Rotation by matrix" )
        {
            mat4f m = matMakeRotation<float>( { 0.f, 0.f, 1.f }, CHESTNUT_PI_F );

            v = m * v;

            REQUIRE( v.x == Approx(-1.f).margin(0.001) );
            REQUIRE( v.y == Approx(-2.f).margin(0.001) );
            REQUIRE( v.z == Approx(3.f).margin(0.001) );
        }

        SECTION( "Rotation by function" )
        {
            vecRotate( v, { 0.f, 0.f, 1.f }, CHESTNUT_PI_F );

            REQUIRE( v.x == Approx(-1.f).margin(0.001) );
            REQUIRE( v.y == Approx(-2.f).margin(0.001) );
            REQUIRE( v.z == Approx(3.f).margin(0.001) );
        }
    }

    SECTION( "vec4 transform" )
    {
        vec4f v = { 1.f, 2.f, 3.f, 1.f };

        SECTION( "Translation by matrix" )
        {
            mat4f m  = matMakeTranslation<float>( 4.f, 5.f, 6.f );

            v = m * v;

            REQUIRE( v.x == Approx(5.f).margin(0.001) );
            REQUIRE( v.y == Approx(7.f).margin(0.001) );
            REQUIRE( v.z == Approx(9.f).margin(0.001) );
            REQUIRE( v.w == Approx(1.f).margin(0.001) );
        }

        SECTION( "Translation by function" )
        {
            vecTranslate( v, 4.f, 5.f, 6.f );

            REQUIRE( v.x == Approx(5.f).margin(0.001) );
            REQUIRE( v.y == Approx(7.f).margin(0.001) );
            REQUIRE( v.z == Approx(9.f).margin(0.001) );
            REQUIRE( v.w == Approx(1.f).margin(0.001) );
        }

        SECTION( "Scale by matrix" )
        {
            mat4f m = matMakeScale<float>( 4.f, 5.f, 6.f );

            v = m * v;

            REQUIRE( v.x == Approx(4.f).margin(0.001) );
            REQUIRE( v.y == Approx(10.f).margin(0.001) );
            REQUIRE( v.z == Approx(18.f).margin(0.001) );
            REQUIRE( v.w == Approx(1.f).margin(0.001) );
        }

        SECTION( "Scale by function" )
        {
            vecScale( v, 4.f, 5.f, 6.f );

            REQUIRE( v.x == Approx(4.f).margin(0.001) );
            REQUIRE( v.y == Approx(10.f).margin(0.001) );
            REQUIRE( v.z == Approx(18.f).margin(0.001) );
            REQUIRE( v.w == Approx(1.f).margin(0.001) );
        }

        SECTION( "Rotation by matrix" )
        {
            mat4f m = matMakeRotation<float>( { 0.f, 0.f, 1.f }, CHESTNUT_PI_F );

            v = m * v;

            REQUIRE( v.x == Approx(-1.f).margin(0.001) );
            REQUIRE( v.y == Approx(-2.f).margin(0.001) );
            REQUIRE( v.z == Approx(3.f).margin(0.001) );
            REQUIRE( v.w == Approx(1.f).margin(0.001) );
        }

        SECTION( "Rotation by function" )
        {
            vecRotate( v, { 0.f, 0.f, 1.f }, CHESTNUT_PI_F );

            REQUIRE( v.x == Approx(-1.f).margin(0.001) );
            REQUIRE( v.y == Approx(-2.f).margin(0.001) );
            REQUIRE( v.z == Approx(3.f).margin(0.001) );
            REQUIRE( v.w == Approx(1.f).margin(0.001) );
        }
    }
}