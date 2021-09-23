#include <catch2/catch.hpp>

#include "../src/chestnut/engine/maths/matrix.hpp"


using namespace chestnut;

typedef Matrix<float,4> mat4f;

TEST_CASE( "N-size matrix test" )
{
    SECTION( "Setters and getters consistency" )
    {
        mat4f m;

        m.set(0,0, 1.f); m.set(0,1, 5.f); m.set(0,2, 9.f);  m.set(0,3, 13.f);
        m.set(1,0, 2.f); m.set(1,1, 6.f); m.set(1,2, 10.f); m.set(1,3, 14.f);
        m.set(2,0, 3.f); m.set(2,1, 7.f); m.set(2,2, 11.f); m.set(2,3, 15.f);
        m.set(3,0, 4.f); m.set(3,1, 8.f); m.set(3,2, 12.f); m.set(3,3, 16.f);


        REQUIRE( m.elements[0] == Approx(1.f).margin(0.001) );
        REQUIRE( m.get(0,0) == Approx(1.f).margin(0.001) );
        REQUIRE( m(0,0) == Approx(1.f).margin(0.001) );

        REQUIRE( m.elements[1] == Approx(2.f).margin(0.001) );
        REQUIRE( m.get(1,0) == Approx(2.f).margin(0.001) );
        REQUIRE( m(1,0) == Approx(2.f).margin(0.001) );

        REQUIRE( m.elements[2] == Approx(3.f).margin(0.001) );
        REQUIRE( m.get(2,0) == Approx(3.f).margin(0.001) );
        REQUIRE( m(2,0) == Approx(3.f).margin(0.001) );

        REQUIRE( m.elements[3] == Approx(4.f).margin(0.001) );
        REQUIRE( m.get(3,0) == Approx(4.f).margin(0.001) );
        REQUIRE( m(3,0) == Approx(4.f).margin(0.001) );


        REQUIRE( m.elements[4] == Approx(5.f).margin(0.001) );
        REQUIRE( m.get(0,1) == Approx(5.f).margin(0.001) );
        REQUIRE( m(0,1) == Approx(5.f).margin(0.001) );

        REQUIRE( m.elements[5] == Approx(6.f).margin(0.001) );
        REQUIRE( m.get(1,1) == Approx(6.f).margin(0.001) );
        REQUIRE( m(1,1) == Approx(6.f).margin(0.001) );

        REQUIRE( m.elements[6] == Approx(7.f).margin(0.001) );
        REQUIRE( m.get(2,1) == Approx(7.f).margin(0.001) );
        REQUIRE( m(2,1) == Approx(7.f).margin(0.001) );

        REQUIRE( m.elements[7] == Approx(8.f).margin(0.001) );
        REQUIRE( m.get(3,1) == Approx(8.f).margin(0.001) );
        REQUIRE( m(3,1) == Approx(8.f).margin(0.001) );


        REQUIRE( m.elements[8] == Approx(9.f).margin(0.001) );
        REQUIRE( m.get(0,2) == Approx(9.f).margin(0.001) );
        REQUIRE( m(0,2) == Approx(9.f).margin(0.001) );

        REQUIRE( m.elements[9] == Approx(10.f).margin(0.001) );
        REQUIRE( m.get(1,2) == Approx(10.f).margin(0.001) );
        REQUIRE( m(1,2) == Approx(10.f).margin(0.001) );

        REQUIRE( m.elements[10] == Approx(11.f).margin(0.001) );
        REQUIRE( m.get(2,2) == Approx(11.f).margin(0.001) );
        REQUIRE( m(2,2) == Approx(11.f).margin(0.001) );

        REQUIRE( m.elements[11] == Approx(12.f).margin(0.001) );
        REQUIRE( m.get(3,2) == Approx(12.f).margin(0.001) );
        REQUIRE( m(3,2) == Approx(12.f).margin(0.001) );

        
        REQUIRE( m.elements[12] == Approx(13.f).margin(0.001) );
        REQUIRE( m.get(0,3) == Approx(13.f).margin(0.001) );
        REQUIRE( m(0,3) == Approx(13.f).margin(0.001) );

        REQUIRE( m.elements[13] == Approx(14.f).margin(0.001) );
        REQUIRE( m.get(1,3) == Approx(14.f).margin(0.001) );
        REQUIRE( m(1,3) == Approx(14.f).margin(0.001) );

        REQUIRE( m.elements[14] == Approx(15.f).margin(0.001) );
        REQUIRE( m.get(2,3) == Approx(15.f).margin(0.001) );
        REQUIRE( m(2,3) == Approx(15.f).margin(0.001) );

        REQUIRE( m.elements[15] == Approx(16.f).margin(0.001) );
        REQUIRE( m.get(3,3) == Approx(16.f).margin(0.001) );
        REQUIRE( m(3,3) == Approx(16.f).margin(0.001) );
    }

    SECTION( "Default constructor" )
    {
        mat4f m;

        REQUIRE( m(0,0) == Approx(1.f).margin(0.001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,1) == Approx(1.f).margin(0.001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,2) == Approx(1.f).margin(0.001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.001) );
    }

    SECTION( "Scalar constructor" )
    {
        mat4f m(3.f);

        REQUIRE( m(0,0) == Approx(3.f).margin(0.001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,1) == Approx(3.f).margin(0.001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,2) == Approx(3.f).margin(0.001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,3) == Approx(3.f).margin(0.001) );
    }

    SECTION( "Matrix identity" )
    {
        mat4f m = matIdentity<float,4>();

        REQUIRE( m(0,0) == Approx(1.f).margin(0.001) );
        REQUIRE( m(1,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,0) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,0) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,1) == Approx(1.f).margin(0.001) );
        REQUIRE( m(2,1) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,1) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,2) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,2) == Approx(1.f).margin(0.001) );
        REQUIRE( m(3,2) == Approx(0.f).margin(0.001) );

        REQUIRE( m(0,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(1,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(2,3) == Approx(0.f).margin(0.001) );
        REQUIRE( m(3,3) == Approx(1.f).margin(0.001) );
    }

    SECTION( "Matrix transposed" )
    {
        mat4f m;

        m(0,0) = 1.f; m(0,1) = 5.f; m(0,2) =  9.f; m(0,3) = 13.f;
        m(1,0) = 2.f; m(1,1) = 6.f; m(1,2) = 10.f; m(1,3) = 14.f;
        m(2,0) = 3.f; m(2,1) = 7.f; m(2,2) = 11.f; m(2,3) = 15.f;
        m(3,0) = 4.f; m(3,1) = 8.f; m(3,2) = 12.f; m(3,3) = 16.f;

        mat4f mt = matTransposed(m);

        REQUIRE( mt(0,0) == Approx(1.f).margin(0.001) );
        REQUIRE( mt(1,0) == Approx(5.f).margin(0.001) );
        REQUIRE( mt(2,0) == Approx(9.f).margin(0.001) );
        REQUIRE( mt(3,0) == Approx(13.f).margin(0.001) );

        REQUIRE( mt(0,1) == Approx(2.f).margin(0.001) );
        REQUIRE( mt(1,1) == Approx(6.f).margin(0.001) );
        REQUIRE( mt(2,1) == Approx(10.f).margin(0.001) );
        REQUIRE( mt(3,1) == Approx(14.f).margin(0.001) );

        REQUIRE( mt(0,2) == Approx(3.f).margin(0.001) );
        REQUIRE( mt(1,2) == Approx(7.f).margin(0.001) );
        REQUIRE( mt(2,2) == Approx(11.f).margin(0.001) );
        REQUIRE( mt(3,2) == Approx(15.f).margin(0.001) );

        REQUIRE( mt(0,3) == Approx(4.f).margin(0.001) );
        REQUIRE( mt(1,3) == Approx(8.f).margin(0.001) );
        REQUIRE( mt(2,3) == Approx(12.f).margin(0.001) );
        REQUIRE( mt(3,3) == Approx(16.f).margin(0.001) );
    }

    SECTION( "Matrix negation" )
    {
        mat4f m;

        m(0,0) =  1.f; m(0,1) =  5.f; m(0,2) =   9.f; m(0,3) =  13.f;
        m(1,0) = -2.f; m(1,1) = -6.f; m(1,2) = -10.f; m(1,3) = -14.f;
        m(2,0) =  3.f; m(2,1) =  7.f; m(2,2) =  11.f; m(2,3) =  15.f;
        m(3,0) = -4.f; m(3,1) = -8.f; m(3,2) = -12.f; m(3,3) = -16.f;

        mat4f mn = matNegated(m);

        REQUIRE( mn(0,0) == Approx(-1.f).margin(0.001) );
        REQUIRE( mn(1,0) == Approx(2.f).margin(0.001) );
        REQUIRE( mn(2,0) == Approx(-3.f).margin(0.001) );
        REQUIRE( mn(3,0) == Approx(4.f).margin(0.001) );

        REQUIRE( mn(0,1) == Approx(-5.f).margin(0.001) );
        REQUIRE( mn(1,1) == Approx(6.f).margin(0.001) );
        REQUIRE( mn(2,1) == Approx(-7.f).margin(0.001) );
        REQUIRE( mn(3,1) == Approx(8.f).margin(0.001) );

        REQUIRE( mn(0,2) == Approx(-9.f).margin(0.001) );
        REQUIRE( mn(1,2) == Approx(10.f).margin(0.001) );
        REQUIRE( mn(2,2) == Approx(-11.f).margin(0.001) );
        REQUIRE( mn(3,2) == Approx(12.f).margin(0.001) );

        REQUIRE( mn(0,3) == Approx(-13.f).margin(0.001) );
        REQUIRE( mn(1,3) == Approx(14.f).margin(0.001) );
        REQUIRE( mn(2,3) == Approx(-15.f).margin(0.001) );
        REQUIRE( mn(3,3) == Approx(16.f).margin(0.001) );
    }

    SECTION( "Matrix sum" )
    {
        mat4f m1, m2;

        m1(0,0) = 1.f; m1(0,1) = 5.f; m1(0,2) =  9.f; m1(0,3) = 13.f;
        m1(1,0) = 2.f; m1(1,1) = 6.f; m1(1,2) = 10.f; m1(1,3) = 14.f;
        m1(2,0) = 3.f; m1(2,1) = 7.f; m1(2,2) = 11.f; m1(2,3) = 15.f;
        m1(3,0) = 4.f; m1(3,1) = 8.f; m1(3,2) = 12.f; m1(3,3) = 16.f;

        m2(0,0) = 17.f; m2(0,1) = 21.f; m2(0,2) = 25.f; m2(0,3) = 29.f;
        m2(1,0) = 18.f; m2(1,1) = 22.f; m2(1,2) = 26.f; m2(1,3) = 30.f;
        m2(2,0) = 19.f; m2(2,1) = 23.f; m2(2,2) = 27.f; m2(2,3) = 31.f;
        m2(3,0) = 20.f; m2(3,1) = 24.f; m2(3,2) = 28.f; m2(3,3) = 32.f;

        mat4f ms = m1 + m2;

        REQUIRE( ms(0,0) == Approx(18.f).margin(0.001) );
        REQUIRE( ms(1,0) == Approx(20.f).margin(0.001) );
        REQUIRE( ms(2,0) == Approx(22.f).margin(0.001) );
        REQUIRE( ms(3,0) == Approx(24.f).margin(0.001) );

        REQUIRE( ms(0,1) == Approx(26.f).margin(0.001) );
        REQUIRE( ms(1,1) == Approx(28.f).margin(0.001) );
        REQUIRE( ms(2,1) == Approx(30.f).margin(0.001) );
        REQUIRE( ms(3,1) == Approx(32.f).margin(0.001) );

        REQUIRE( ms(0,2) == Approx(34.f).margin(0.001) );
        REQUIRE( ms(1,2) == Approx(36.f).margin(0.001) );
        REQUIRE( ms(2,2) == Approx(38.f).margin(0.001) );
        REQUIRE( ms(3,2) == Approx(40.f).margin(0.001) );

        REQUIRE( ms(0,3) == Approx(42.f).margin(0.001) );
        REQUIRE( ms(1,3) == Approx(44.f).margin(0.001) );
        REQUIRE( ms(2,3) == Approx(46.f).margin(0.001) );
        REQUIRE( ms(3,3) == Approx(48.f).margin(0.001) );
    }

    SECTION( "Matrix difference" )
    {
        mat4f m1, m2;

        m1(0,0) = 1.f; m1(0,1) = 5.f; m1(0,2) =  9.f; m1(0,3) = 13.f;
        m1(1,0) = 2.f; m1(1,1) = 6.f; m1(1,2) = 10.f; m1(1,3) = 14.f;
        m1(2,0) = 3.f; m1(2,1) = 7.f; m1(2,2) = 11.f; m1(2,3) = 15.f;
        m1(3,0) = 4.f; m1(3,1) = 8.f; m1(3,2) = 12.f; m1(3,3) = 16.f;

        m2(0,0) = 16.f; m2(0,1) = 12.f; m2(0,2) = 8.f; m2(0,3) = 4.f;
        m2(1,0) = 15.f; m2(1,1) = 11.f; m2(1,2) = 7.f; m2(1,3) = 3.f;
        m2(2,0) = 14.f; m2(2,1) = 10.f; m2(2,2) = 6.f; m2(2,3) = 2.f;
        m2(3,0) = 13.f; m2(3,1) =  9.f; m2(3,2) = 5.f; m2(3,3) = 1.f;

        mat4f md = m1 - m2;

        REQUIRE( md(0,0) == Approx(-15.f).margin(0.001) );
        REQUIRE( md(1,0) == Approx(-13.f).margin(0.001) );
        REQUIRE( md(2,0) == Approx(-11.f).margin(0.001) );
        REQUIRE( md(3,0) == Approx( -9.f).margin(0.001) );

        REQUIRE( md(0,1) == Approx(-7.f).margin(0.001) );
        REQUIRE( md(1,1) == Approx(-5.f).margin(0.001) );
        REQUIRE( md(2,1) == Approx(-3.f).margin(0.001) );
        REQUIRE( md(3,1) == Approx(-1.f).margin(0.001) );

        REQUIRE( md(0,2) == Approx(1.f).margin(0.001) );
        REQUIRE( md(1,2) == Approx(3.f).margin(0.001) );
        REQUIRE( md(2,2) == Approx(5.f).margin(0.001) );
        REQUIRE( md(3,2) == Approx(7.f).margin(0.001) );

        REQUIRE( md(0,3) == Approx(9.f).margin(0.001) );
        REQUIRE( md(1,3) == Approx(11.f).margin(0.001) );
        REQUIRE( md(2,3) == Approx(13.f).margin(0.001) );
        REQUIRE( md(3,3) == Approx(15.f).margin(0.001) );
    }

    SECTION( "Matrix product" )
    {
        mat4f m1, m2;

        m1(0,0) = 1.f; m1(0,1) = 5.f; m1(0,2) =  9.f; m1(0,3) = 13.f;
        m1(1,0) = 2.f; m1(1,1) = 6.f; m1(1,2) = 10.f; m1(1,3) = 14.f;
        m1(2,0) = 3.f; m1(2,1) = 7.f; m1(2,2) = 11.f; m1(2,3) = 15.f;
        m1(3,0) = 4.f; m1(3,1) = 8.f; m1(3,2) = 12.f; m1(3,3) = 16.f;

        m2(0,0) = 16.f; m2(0,1) = 12.f; m2(0,2) = 8.f; m2(0,3) = 4.f;
        m2(1,0) = 15.f; m2(1,1) = 11.f; m2(1,2) = 7.f; m2(1,3) = 3.f;
        m2(2,0) = 14.f; m2(2,1) = 10.f; m2(2,2) = 6.f; m2(2,3) = 2.f;
        m2(3,0) = 13.f; m2(3,1) =  9.f; m2(3,2) = 5.f; m2(3,3) = 1.f;

        mat4f mp = m1 * m2;

        REQUIRE( mp(0,0) == Approx(386.f).margin(0.001) );
        REQUIRE( mp(1,0) == Approx(444.f).margin(0.001) );
        REQUIRE( mp(2,0) == Approx(502.f).margin(0.001) );
        REQUIRE( mp(3,0) == Approx(560.f).margin(0.001) );

        REQUIRE( mp(0,1) == Approx(274.f).margin(0.001) );
        REQUIRE( mp(1,1) == Approx(316.f).margin(0.001) );
        REQUIRE( mp(2,1) == Approx(358.f).margin(0.001) );
        REQUIRE( mp(3,1) == Approx(400.f).margin(0.001) );

        REQUIRE( mp(0,2) == Approx(162.f).margin(0.001) );
        REQUIRE( mp(1,2) == Approx(188.f).margin(0.001) );
        REQUIRE( mp(2,2) == Approx(214.f).margin(0.001) );
        REQUIRE( mp(3,2) == Approx(240.f).margin(0.001) );

        REQUIRE( mp(0,3) == Approx(50.f).margin(0.001) );
        REQUIRE( mp(1,3) == Approx(60.f).margin(0.001) );
        REQUIRE( mp(2,3) == Approx(70.f).margin(0.001) );
        REQUIRE( mp(3,3) == Approx(80.f).margin(0.001) );
    }

    SECTION( "Matrix scalar product" )
    {
        mat4f m;

        m(0,0) = 1.f; m(0,1) = 5.f; m(0,2) =  9.f; m(0,3) = 13.f;
        m(1,0) = 2.f; m(1,1) = 6.f; m(1,2) = 10.f; m(1,3) = 14.f;
        m(2,0) = 3.f; m(2,1) = 7.f; m(2,2) = 11.f; m(2,3) = 15.f;
        m(3,0) = 4.f; m(3,1) = 8.f; m(3,2) = 12.f; m(3,3) = 16.f;

        mat4f mp = m * -2.f;

        REQUIRE( mp(0,0) == Approx(-2.f).margin(0.001) );
        REQUIRE( mp(1,0) == Approx(-4.f).margin(0.001) );
        REQUIRE( mp(2,0) == Approx(-6.f).margin(0.001) );
        REQUIRE( mp(3,0) == Approx(-8.f).margin(0.001) );

        REQUIRE( mp(0,1) == Approx(-10.f).margin(0.001) );
        REQUIRE( mp(1,1) == Approx(-12.f).margin(0.001) );
        REQUIRE( mp(2,1) == Approx(-14.f).margin(0.001) );
        REQUIRE( mp(3,1) == Approx(-16.f).margin(0.001) );

        REQUIRE( mp(0,2) == Approx(-18.f).margin(0.001) );
        REQUIRE( mp(1,2) == Approx(-20.f).margin(0.001) );
        REQUIRE( mp(2,2) == Approx(-22.f).margin(0.001) );
        REQUIRE( mp(3,2) == Approx(-24.f).margin(0.001) );

        REQUIRE( mp(0,3) == Approx(-26.f).margin(0.001) );
        REQUIRE( mp(1,3) == Approx(-28.f).margin(0.001) );
        REQUIRE( mp(2,3) == Approx(-30.f).margin(0.001) );
        REQUIRE( mp(3,3) == Approx(-32.f).margin(0.001) );
    }
}