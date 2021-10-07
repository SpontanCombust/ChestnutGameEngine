#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/vector4.hpp"

#include <cmath>


using namespace chestnut::engine;

TEST_CASE( "Math - 4-size vector test" )
{
    SECTION( "Default state" )
    {
        vec4f v;

        REQUIRE( v.x == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(0.0).margin(0.001) );
        REQUIRE( v.y == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(0.0).margin(0.001) );
        REQUIRE( v.z == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(0.0).margin(0.001) );
        REQUIRE( v.w == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[3] == Approx(0.0).margin(0.001) );
    }

    SECTION( "Scalar constructor" )
    {
        vec4f v = vec4f(3.f);

        REQUIRE( v.x == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(3.0).margin(0.001) );
        REQUIRE( v.y == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(3.0).margin(0.001) );
        REQUIRE( v.z == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(3.0).margin(0.001) );
        REQUIRE( v.w == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[3] == Approx(3.0).margin(0.001) );
    }

    SECTION( "Component constructor" )
    {
        vec4f v = vec4f( 1.f, 2.f, 3.f, 4.f );

        REQUIRE( v.x == Approx(1.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(1.0).margin(0.001) );
        REQUIRE( v.y == Approx(2.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(2.0).margin(0.001) );
        REQUIRE( v.z == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(3.0).margin(0.001) );
        REQUIRE( v.w == Approx(4.0).margin(0.001) );
        REQUIRE( v.data()[3] == Approx(4.0).margin(0.001) );
    }

    SECTION( "Magnitude" )
    {
        vec4f v;
        v.x = 1.f;
        v.y = 2.f;
        v.z = 3.f;
        v.w = 4.f;

        REQUIRE( vecMagnitude(v) == Approx( std::sqrt(30.f) ) );
    }

    SECTION( "Normalization" )
    {
        vec4f v;
        v.x = 1.f;
        v.y = 2.f;
        v.z = 3.f;
        v.w = 4.f;

        vec4f u = vecNormalized(v);

        REQUIRE( vecMagnitude(u) == Approx(1.0).margin(0.001) );
        REQUIRE( u.x == Approx( 1.f / std::sqrt(30.f) ).margin(0.001) );
        REQUIRE( u.y == Approx( 2.f / std::sqrt(30.f) ).margin(0.001) );
        REQUIRE( u.z == Approx( 3.f / std::sqrt(30.f) ).margin(0.001) );
        REQUIRE( u.w == Approx( 4.f / std::sqrt(30.f) ).margin(0.001) );
    }

    SECTION( "Negation" )
    {
        vec4f v;
        v.x = 1.f;
        v.y = -2.f;
        v.z = 3.f;
        v.w = -4.f;

        vec4f u = -v;

        REQUIRE( u.x == Approx(-1.0).margin(0.001) );
        REQUIRE( u.y == Approx(2.0).margin(0.001) );
        REQUIRE( u.z == Approx(-3.0).margin(0.001) );
        REQUIRE( u.w == Approx(4.0).margin(0.001) );
    }

    SECTION( "Addition" )
    {
        vec4f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;
        v1.w = 4.f;   v2.w = 5.f;

        vec4f s = v1 + v2;

        REQUIRE( s.x == Approx(3.0).margin(0.001) );
        REQUIRE( s.y == Approx(2.0).margin(0.001) );
        REQUIRE( s.z == Approx(1.0).margin(0.001) );
        REQUIRE( s.w == Approx(9.0).margin(0.001) );


        v1 += v2;
        REQUIRE( v1.x == Approx(3.0).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
        REQUIRE( v1.z == Approx(1.0).margin(0.001) );
        REQUIRE( v1.w == Approx(9.0).margin(0.001) );
    }

    SECTION( "Subtraction" )
    {
        vec4f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;
        v1.w = 4.f;   v2.w = 5.f;

        vec4f d = v1 - v2;

        REQUIRE( d.x == Approx(-1.0).margin(0.001) );
        REQUIRE( d.y == Approx(2.0).margin(0.001) );
        REQUIRE( d.z == Approx(5.0).margin(0.001) );
        REQUIRE( d.w == Approx(-1.0).margin(0.001) );


        v1 -= v2;
        REQUIRE( v1.x == Approx(-1.0).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
        REQUIRE( v1.z == Approx(5.0).margin(0.001) );
        REQUIRE( v1.w == Approx(-1.0).margin(0.001) );
    }

    SECTION( "Component product" )
    {
        vec4f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;
        v1.w = 4.f;   v2.w = 5.f;

        vec4f p = v1 * v2;

        REQUIRE( p.x == Approx(2.0).margin(0.001) );
        REQUIRE( p.y == Approx(0.0).margin(0.001) );
        REQUIRE( p.z == Approx(-6.0).margin(0.001) );
        REQUIRE( p.w == Approx(20.0).margin(0.001) );


        v1 *= v2;
        REQUIRE( v1.x == Approx(2.0).margin(0.001) );
        REQUIRE( v1.y == Approx(0.0).margin(0.001) );
        REQUIRE( v1.z == Approx(-6.0).margin(0.001) );
        REQUIRE( v1.w == Approx(20.0).margin(0.001) );
    }

    SECTION( "Component quotient" )
    {    
        vec4f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 1.f;
        v1.z = 3.f;   v2.z = -2.f;
        v1.w = 4.f;   v2.w = 5.f;

        vec4f q = v1 / v2;

        REQUIRE( q.x == Approx(0.5).margin(0.001) );
        REQUIRE( q.y == Approx(2.0).margin(0.001) );
        REQUIRE( q.z == Approx(-1.5).margin(0.001) );
        REQUIRE( q.w == Approx(0.8).margin(0.001) );


        v1 /= v2;
        REQUIRE( v1.x == Approx(0.5).margin(0.001) );
        REQUIRE( v1.y == Approx(2.0).margin(0.001) );
        REQUIRE( v1.z == Approx(-1.5).margin(0.001) );
        REQUIRE( v1.w == Approx(0.8).margin(0.001) );
    }

    SECTION( "Scalar product" )
    {
        vec4f v;
        v.x = 1.f;
        v.y = 2.f;
        v.z = 3.f;
        v.w = -4.f;

        vec4f u = -2.5f * v;

        REQUIRE( u.x == Approx(-2.5).margin(0.001) );
        REQUIRE( u.y == Approx(-5.0).margin(0.001) );
        REQUIRE( u.z == Approx(-7.5).margin(0.001) );
        REQUIRE( u.w == Approx(10.0).margin(0.001) );


        v *= -2.5f;
        REQUIRE( v.x == Approx(-2.5).margin(0.001) );
        REQUIRE( v.y == Approx(-5.0).margin(0.001) );
        REQUIRE( v.z == Approx(-7.5).margin(0.001) );
        REQUIRE( v.w == Approx(10.0).margin(0.001) );
    }
    
    SECTION( "Scalar quotient" )
    {
        vec4f v;
        v.x = 1.f;
        v.y = 2.f;
        v.z = 3.f;
        v.w = -4.f;

        vec4f u = v / -2.f;

        REQUIRE( u.x == Approx(-0.5).margin(0.001) );
        REQUIRE( u.y == Approx(-1.0).margin(0.001) );
        REQUIRE( u.z == Approx(-1.5).margin(0.001) );
        REQUIRE( u.w == Approx(2.0).margin(0.001) );


        v /= -2.f;
        REQUIRE( u.x == Approx(-0.5).margin(0.001) );
        REQUIRE( u.y == Approx(-1.0).margin(0.001) );
        REQUIRE( u.z == Approx(-1.5).margin(0.001) );
        REQUIRE( u.w == Approx(2.0).margin(0.001) );
    }

    SECTION( "Dot product" )
    {
        vec4f v1, v2;
        v1.x = 1.f;   v2.x = 2.f;
        v1.y = 2.f;   v2.y = 0.f;
        v1.z = 3.f;   v2.z = -2.f;
        v1.w = 4.f;   v2.w = 5.f;

        float p = vecDotProduct( v1, v2 );

        REQUIRE( p == Approx(16.0).margin(0.001) );   
    }
}