#include <catch2/catch.hpp>

#include "../src/engine/maths/vector2.hpp"

#include <cmath>


using namespace chestnut;

TEST_CASE( "2-size vector test" )
{
    SECTION( "Default state" )
    {
        vec2f v;

        REQUIRE( v.x == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(0.0).margin(0.001) );
        REQUIRE( v.y == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(0.0).margin(0.001) );
    }

    SECTION( "Scalar constructor" )
    {
        vec2f v = vec2f(3.f);

        REQUIRE( v.x == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(3.0).margin(0.001) );
        REQUIRE( v.y == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(3.0).margin(0.001) );
    }

    SECTION( "Component constructor" )
    {
        vec2f v = vec2f( 2.f, -5.f );

        REQUIRE( v.x == Approx(2.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(2.0).margin(0.001) );
        REQUIRE( v.y == Approx(-5.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(-5.0).margin(0.001) );
    }

    SECTION( "Magnitude" )
    {
        vec2f v;
        v.x = 1.f;
        v.y = 2.f;

        REQUIRE( vecMagnitude(v) == Approx( std::sqrt(5.f) ) );
    }

    SECTION( "Normalization" )
    {
        vec2f v;
        v.x = 1.f;
        v.y = 2.f;

        vec2f u = vecNormalized(v);

        REQUIRE( vecMagnitude(u) == Approx(1.0).margin(0.001) );
        REQUIRE( u.x == Approx( 1.f / std::sqrt(5.f) ).margin(0.001) );
        REQUIRE( u.y == Approx( 2.f / std::sqrt(5.f) ).margin(0.001) );
    }

    SECTION( "Negation" )
    {
        vec2f v;
        v.x = 1.f;
        v.y = -2.f;

        vec2f u = -v;

        REQUIRE( u.x == Approx(-1.0).margin(0.001) );
        REQUIRE( u.y == Approx(2.0).margin(0.001) );
    }

    SECTION( "Addition" )
    {
        vec2f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;

        vec2f s = v1 + v2;

        REQUIRE( s.x == Approx(3.0).margin(0.001) );
        REQUIRE( s.y == Approx(2.0).margin(0.001) );


        v1 += v2;
        REQUIRE( v1.x == Approx(3.0).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
    }

    SECTION( "Subtraction" )
    {
        vec2f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;

        vec2f d = v1 - v2;

        REQUIRE( d.x == Approx(-1.0).margin(0.001) );
        REQUIRE( d.y == Approx(2.0).margin(0.001) );


        v1 -= v2;
        REQUIRE( v1.x == Approx(-1.0).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
    }

    SECTION( "Component product" )
    {
        vec2f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;

        vec2f p = v1 * v2;

        REQUIRE( p.x == Approx(2.0).margin(0.001) );
        REQUIRE( p.y == Approx(0.0).margin(0.001) );


        v1 *= v2;
        REQUIRE( v1.x == Approx(2.0).margin(0.001) );
        REQUIRE( v1.y == Approx(0.0).margin(0.001) );
    }

    SECTION( "Component quotient" )
    {
        
        vec2f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 1.f;

        vec2f q = v1 / v2;

        REQUIRE( q.x == Approx(0.5).margin(0.001) );
        REQUIRE( q.y == Approx(2.0).margin(0.001) );


        v1 /= v2;
        REQUIRE( v1.x == Approx(0.5).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
    }

    SECTION( "Scalar product" )
    {
        vec2f v;
        v.x = 1.f;
        v.y = 2.f;

        vec2f u = -2.5f * v;

        REQUIRE( u.x == Approx(-2.5).margin(0.001) );
        REQUIRE( u.y == Approx(-5.0).margin(0.001) );


        v *= -2.5f;
        REQUIRE( v.x == Approx(-2.5).margin(0.001) );
        REQUIRE( v.y == Approx(-5.0).margin(0.001) );
    }

    SECTION( "Dot product" )
    {
        vec2f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;

        float p = vecDotProduct( v1, v2 );

        REQUIRE( p == Approx(2.0).margin(0.001) );   
    }
}