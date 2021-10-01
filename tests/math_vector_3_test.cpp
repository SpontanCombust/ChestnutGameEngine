#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/vector3.hpp"

#include <cmath>


using namespace chestnut::engine;

TEST_CASE( "3-size vector test" )
{
    SECTION( "Default state" )
    {
        vec3f v;

        REQUIRE( v.x == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(0.0).margin(0.001) );
        REQUIRE( v.y == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(0.0).margin(0.001) );
        REQUIRE( v.z == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(0.0).margin(0.001) );
    }

    SECTION( "Scalar constructor" )
    {
        vec3f v = vec3f(3.f);

        REQUIRE( v.x == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(3.0).margin(0.001) );
        REQUIRE( v.y == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(3.0).margin(0.001) );
        REQUIRE( v.z == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(3.0).margin(0.001) );
    }

    SECTION( "Component constructor" )
    {
        vec3f v = vec3f( 1.f, 2.f, 3.f );

        REQUIRE( v.x == Approx(1.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(1.0).margin(0.001) );
        REQUIRE( v.y == Approx(2.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(2.0).margin(0.001) );
        REQUIRE( v.z == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(3.0).margin(0.001) );
    }

    SECTION( "Magnitude" )
    {
        vec3f v;
        v.x = 1.f;
        v.y = 2.f;
        v.z = 3.f;

        REQUIRE( vecMagnitude(v) == Approx( std::sqrt(14.f) ) );
    }

    SECTION( "Normalization" )
    {
        vec3f v;
        v.x = 1.f;
        v.y = 2.f;
        v.z = 3.f;

        vec3f u = vecNormalized(v);

        REQUIRE( vecMagnitude(u) == Approx(1.0).margin(0.001) );
        REQUIRE( u.x == Approx( 1.f / std::sqrt(14.f) ).margin(0.001) );
        REQUIRE( u.y == Approx( 2.f / std::sqrt(14.f) ).margin(0.001) );
        REQUIRE( u.z == Approx( 3.f / std::sqrt(14.f) ).margin(0.001) );
    }

    SECTION( "Negation" )
    {
        vec3f v;
        v.x = 1.f;
        v.y = -2.f;
        v.z = 3.f;

        vec3f u = -v;

        REQUIRE( u.x == Approx(-1.0).margin(0.001) );
        REQUIRE( u.y == Approx(2.0).margin(0.001) );
        REQUIRE( u.z == Approx(-3.0).margin(0.001) );
    }

    SECTION( "Addition" )
    {
        vec3f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;

        vec3f s = v1 + v2;

        REQUIRE( s.x == Approx(3.0).margin(0.001) );
        REQUIRE( s.y == Approx(2.0).margin(0.001) );
        REQUIRE( s.z == Approx(1.0).margin(0.001) );


        v1 += v2;
        REQUIRE( v1.x == Approx(3.0).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
        REQUIRE( v1.z == Approx(1.0).margin(0.001) );
    }

    SECTION( "Subtraction" )
    {
        vec3f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;

        vec3f d = v1 - v2;

        REQUIRE( d.x == Approx(-1.0).margin(0.001) );
        REQUIRE( d.y == Approx(2.0).margin(0.001) );
        REQUIRE( d.z == Approx(5.0).margin(0.001) );


        v1 -= v2;
        REQUIRE( v1.x == Approx(-1.0).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
        REQUIRE( v1.z == Approx(5.0).margin(0.001) );
    }

    SECTION( "Component product" )
    {
        vec3f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;

        vec3f p = v1 * v2;

        REQUIRE( p.x == Approx(2.0).margin(0.001) );
        REQUIRE( p.y == Approx(0.0).margin(0.001) );
        REQUIRE( p.z == Approx(-6.0).margin(0.001) );


        v1 *= v2;
        REQUIRE( v1.x == Approx(2.0).margin(0.001) );
        REQUIRE( v1.y == Approx(0.0).margin(0.001) );
        REQUIRE( v1.z == Approx(-6.0).margin(0.001) );
    }

    SECTION( "Component quotient" )
    {
        
        vec3f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 1.f;
        v1.z = 3.f;   v2.z = -2.f;

        vec3f q = v1 / v2;

        REQUIRE( q.x == Approx(0.5).margin(0.001) );
        REQUIRE( q.y == Approx(2.0).margin(0.001) );
        REQUIRE( q.z == Approx(-1.5).margin(0.001) );


        v1 /= v2;
        REQUIRE( v1.x == Approx(0.5).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
        REQUIRE( v1.z == Approx(-1.5).margin(0.001) );
    }

    SECTION( "Scalar product" )
    {
        vec3f v;
        v.x = 1.f;
        v.y = 2.f;
        v.z = 3.f;

        vec3f u = -2.5f * v;

        REQUIRE( u.x == Approx(-2.5).margin(0.001) );
        REQUIRE( u.y == Approx(-5.0).margin(0.001) );
        REQUIRE( u.z == Approx(-7.5).margin(0.001) );


        v *= -2.5f;
        REQUIRE( v.x == Approx(-2.5).margin(0.001) );
        REQUIRE( v.y == Approx(-5.0).margin(0.001) );
        REQUIRE( v.z == Approx(-7.5).margin(0.001) );
    }

    SECTION( "Dot product" )
    {
        vec3f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;

        float p = vecDotProduct( v1, v2 );

        REQUIRE( p == Approx(-4.0).margin(0.001) );   
    }

    SECTION( "Cross product vec2" )
    {
        vec2f v1 { 1.f, 2.f };
        vec2f v2 { 3.f, 4.f };

        vec3f p = vecCrossProduct( v1, v2 );

        REQUIRE( p.x == Approx(0.0).margin(0.001) );
        REQUIRE( p.y == Approx(0.0).margin(0.001) );
        REQUIRE( p.z == Approx(-2.0).margin(0.001) );
    }

    SECTION( "Cross product vec3" )
    {
        vec3f v1 { 1.f, 2.f, 3.f };
        vec3f v2 { 4.f, 5.f, 6.f };

        vec3f p = vecCrossProduct( v1, v2 );

        REQUIRE( p.x == Approx(-3.0).margin(0.001) );
        REQUIRE( p.y == Approx(6.0).margin(0.001) );
        REQUIRE( p.z == Approx(-3.0).margin(0.001) );
    }
}