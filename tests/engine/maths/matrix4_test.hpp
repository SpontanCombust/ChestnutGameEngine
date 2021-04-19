#ifndef __CHESTNUT_MATRIX4_TEST_H__
#define __CHESTNUT_MATRIX4_TEST_H__

#include "engine/maths/matrix4.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void matrix4Test()
    {
        LOG_CHANNEL( "TEST", "<< toString test >>");
        {
            mat4f m;
            LOG_CHANNEL( "TEST", "\n" << m.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Make ortho/frustum/perspective/translation/scale/rotation test >>");
        {
            mat4f m;

            m = mat4MakeOrthographic<float>( 0, 1980, 1080, 0, 1, -1 );
            LOG_CHANNEL( "TEST", "Orthographic:\n" << m.toString() << "\n" );

            m = mat4MakeFrustum<float>( 0, 1980, 1080, 0, 1, -1 );
            LOG_CHANNEL( "TEST", "Frustum:\n" << m.toString() << "\n" );

            m = mat4MakePerspective<float>( 90.0, 16.0/9.0, 1, -1 );
            LOG_CHANNEL( "TEST", "Perspective:\n" << m.toString() << "\n" );

            m = mat4MakeTranslation<float>( 1, 2, 3 );
            LOG_CHANNEL( "TEST", "Translation [1, 2, 3]:\n" << m.toString() << "\n" );

            m = mat4MakeScale<float>( 1, 2, 3 );
            LOG_CHANNEL( "TEST", "Scale [1, 2, 3]:\n" << m.toString() << "\n" );

            m = mat4MakeRotationX<float>( 1.57 );
            LOG_CHANNEL( "TEST", "Rotation X 180deg:\n" << m.toString() << "\n" );

            m = mat4MakeRotationY<float>( 1.57 );
            LOG_CHANNEL( "TEST", "Rotation Y 180deg:\n" << m.toString() << "\n" );

            m = mat4MakeRotationZ<float>( 1.57 );
            LOG_CHANNEL( "TEST", "Rotation Z 180deg:\n" << m.toString() << "\n" );

            m = mat4MakeRotation<float>( { 1, 0, 0 }, 1.57 );
            LOG_CHANNEL( "TEST", "Rotation 180deg around [1,0,0]:\n" << m.toString() << "\n" );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Transposed/negated/sum/difference/product/scalar product test >>");
        {
            mat4f m1 = mat4MakeTranslation<float>( 1, 2, 3 );
            mat4f m2 = mat4MakeScale<float>( 1, 2, 3 );
            mat4f m3;

            LOG_CHANNEL( "TEST", "m1=\n" << m1.toString() << "\n" );
            LOG_CHANNEL( "TEST", "m2=\n" << m2.toString() << "\n" );

            m3 = mat4Transposed(m1);
            LOG_CHANNEL( "TEST", "m3=m1T=\n" << m3.toString() << "\n" );

            m3 = -m1;
            LOG_CHANNEL( "TEST", "m3=-m1=\n" << m3.toString() << "\n" );

            m3 = m1 + m2;
            LOG_CHANNEL( "TEST", "m3=m1+m2=\n" << m3.toString() << "\n" );

            m3 = m1 - m2;
            LOG_CHANNEL( "TEST", "m3=m1-m2=\n" << m3.toString() << "\n" );

            m3 = m1 * m2;
            LOG_CHANNEL( "TEST", "m3=m1*m2=\n" << m3.toString() << "\n" );

            m3 = -2.f * m2;
            LOG_CHANNEL( "TEST", "m3=-2*m2=\n" << m3.toString() << "\n" );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Multiply vector by matrix test >>");
        {
            vec2f v2 = { 0, 3 };
            vec3f v3 = { -1, 0, 4 };
            mat4f m = mat4MakeTranslation<float>( 1, 2, 3 ) * mat4MakeScale<float>( 2, 2, 2 );

            LOG_CHANNEL( "TEST", "v2=" << v2.toString() );
            LOG_CHANNEL( "TEST", "v3=" << v3.toString() );
            LOG_CHANNEL( "TEST", "m=\n" << m.toString() << "\n" );

            LOG_CHANNEL( "TEST", "m*v2=" << ( m * v2 ).toString() );
            LOG_CHANNEL( "TEST", "m*v3=" << ( m * v3 ).toString() );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_MATRIX4_TEST_H__