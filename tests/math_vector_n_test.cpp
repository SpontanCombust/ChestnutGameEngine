#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/vector.hpp"

#include <cmath>


using namespace chestnut::engine;

typedef Vector<float,3> vec3f;

TEST_CASE( "N-size vector test" )
{
    SECTION( "Default state" )
    {
        vec3f v;

        REQUIRE( v.elements[0] == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(0.0).margin(0.001) );
        REQUIRE( v.elements[1] == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(0.0).margin(0.001) );
        REQUIRE( v.elements[2] == Approx(0.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(0.0).margin(0.001) );
    }

    SECTION( "Scalar constructor" )
    {
        vec3f v = vec3f(3.f);

        REQUIRE( v.elements[0] == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[0] == Approx(3.0).margin(0.001) );
        REQUIRE( v.elements[1] == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[1] == Approx(3.0).margin(0.001) );
        REQUIRE( v.elements[2] == Approx(3.0).margin(0.001) );
        REQUIRE( v.data()[2] == Approx(3.0).margin(0.001) );
    }

    SECTION( "Magnitude" )
    {
        vec3f v;
        v.elements[0] = 1.f;
        v.elements[1] = 2.f;
        v.elements[2] = 3.f;

        REQUIRE( vecMagnitude(v) == Approx( std::sqrt(14.f) ) );
    }

    SECTION( "Normalization" )
    {
        vec3f v;
        v.elements[0] = 1.f;
        v.elements[1] = 2.f;
        v.elements[2] = 3.f;

        vec3f u = vecNormalized(v);

        REQUIRE( vecMagnitude(u) == Approx(1.0).margin(0.001) );
        REQUIRE( u.elements[0] == Approx( 1.f / std::sqrt(14.f) ).margin(0.001) );
        REQUIRE( u.elements[1] == Approx( 2.f / std::sqrt(14.f) ).margin(0.001) );
        REQUIRE( u.elements[2] == Approx( 3.f / std::sqrt(14.f) ).margin(0.001) );
    }

    SECTION( "Negation" )
    {
        vec3f v;
        v.elements[0] = 1.f;
        v.elements[1] = -2.f;
        v.elements[2] = 3.f;

        vec3f u = -v;

        REQUIRE( u.elements[0] == Approx(-1.0).margin(0.001) );
        REQUIRE( u.elements[1] == Approx(2.0).margin(0.001) );
        REQUIRE( u.elements[2] == Approx(-3.0).margin(0.001) );
    }

    SECTION( "Addition" )
    {
        vec3f v1, v2;
        v1.elements[0] = 1.f;   v2.elements[0] = 2.f;
        v1.elements[1] = 2.f;   v2.elements[1] = 0.f;
        v1.elements[2] = 3.f;   v2.elements[2] = -2.f;

        vec3f s = v1 + v2;

        REQUIRE( s.elements[0] == Approx(3.0).margin(0.001) );
        REQUIRE( s.elements[1] == Approx(2.0).margin(0.001) );
        REQUIRE( s.elements[2] == Approx(1.0).margin(0.001) );


        v1 += v2;
        REQUIRE( v1.elements[0] == Approx(3.0).margin(0.001) );
        REQUIRE( v1.elements[1] == Approx(2.0).margin(0.001) );
        REQUIRE( v1.elements[2] == Approx(1.0).margin(0.001) );
    }

    SECTION( "Subtraction" )
    {
        vec3f v1, v2;
        v1.elements[0] = 1.f;   v2.elements[0] = 2.f;
        v1.elements[1] = 2.f;   v2.elements[1] = 0.f;
        v1.elements[2] = 3.f;   v2.elements[2] = -2.f;

        vec3f d = v1 - v2;

        REQUIRE( d.elements[0] == Approx(-1.0).margin(0.001) );
        REQUIRE( d.elements[1] == Approx(2.0).margin(0.001) );
        REQUIRE( d.elements[2] == Approx(5.0).margin(0.001) );


        v1 -= v2;
        REQUIRE( v1.elements[0] == Approx(-1.0).margin(0.001) );
        REQUIRE( v1.elements[1] == Approx(2.0).margin(0.001) );
        REQUIRE( v1.elements[2] == Approx(5.0).margin(0.001) );
    }

    SECTION( "Component product" )
    {
        vec3f v1, v2;
        v1.elements[0] = 1.f;   v2.elements[0] = 2.f;
        v1.elements[1] = 2.f;   v2.elements[1] = 0.f;
        v1.elements[2] = 3.f;   v2.elements[2] = -2.f;

        vec3f p = v1 * v2;

        REQUIRE( p.elements[0] == Approx(2.0).margin(0.001) );
        REQUIRE( p.elements[1] == Approx(0.0).margin(0.001) );
        REQUIRE( p.elements[2] == Approx(-6.0).margin(0.001) );


        v1 *= v2;
        REQUIRE( v1.elements[0] == Approx(2.0).margin(0.001) );
        REQUIRE( v1.elements[1] == Approx(0.0).margin(0.001) );
        REQUIRE( v1.elements[2] == Approx(-6.0).margin(0.001) );
    }

    SECTION( "Component quotient" )
    {
        
        vec3f v1, v2;
        v1.elements[0] = 1.f;   v2.elements[0] = 2.f;
        v1.elements[1] = 2.f;   v2.elements[1] = 1.f;
        v1.elements[2] = 3.f;   v2.elements[2] = -2.f;

        vec3f q = v1 / v2;

        REQUIRE( q.elements[0] == Approx(0.5).margin(0.001) );
        REQUIRE( q.elements[1] == Approx(2.0).margin(0.001) );
        REQUIRE( q.elements[2] == Approx(-1.5).margin(0.001) );


        v1 /= v2;
        REQUIRE( v1.elements[0] == Approx(0.5).margin(0.001) );
        REQUIRE( v1.elements[1] == Approx(2.0).margin(0.001) );
        REQUIRE( v1.elements[2] == Approx(-1.5).margin(0.001) );
    }

    SECTION( "Scalar product" )
    {
        vec3f v;
        v.elements[0] = 1.f;
        v.elements[1] = 2.f;
        v.elements[2] = 3.f;

        vec3f u = -2.5f * v;

        REQUIRE( u.elements[0] == Approx(-2.5).margin(0.001) );
        REQUIRE( u.elements[1] == Approx(-5.0).margin(0.001) );
        REQUIRE( u.elements[2] == Approx(-7.5).margin(0.001) );


        v *= -2.5f;
        REQUIRE( v.elements[0] == Approx(-2.5).margin(0.001) );
        REQUIRE( v.elements[1] == Approx(-5.0).margin(0.001) );
        REQUIRE( v.elements[2] == Approx(-7.5).margin(0.001) );
    }

    SECTION( "Dot product" )
    {
        vec3f v1, v2;
        v1.elements[0] = 1.f;   v2.elements[0] = 2.f;
        v1.elements[1] = 2.f;   v2.elements[1] = 0.f;
        v1.elements[2] = 3.f;   v2.elements[2] = -2.f;

        float p = vecDotProduct( v1, v2 );

        REQUIRE( p == Approx(-4.0).margin(0.001) );   
    }
}