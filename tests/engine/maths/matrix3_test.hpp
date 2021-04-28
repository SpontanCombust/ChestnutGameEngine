#ifndef __CHESTNUT_MATRIX3_TEST_H__
#define __CHESTNUT_MATRIX3_TEST_H__

#include "engine/maths/vector3.hpp"
#include "engine/maths/matrix3.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void matrix3Test()
    {
        LOG_CHANNEL( "TEST", "<< toString test >>");
        {
            mat3f m;
            LOG_CHANNEL( "TEST", "\n" << m.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Make translation/scale/rotation test >>");
        {
            mat3f m;

            m = matMakeTranslation<float>( 1, 2 );
            LOG_CHANNEL( "TEST", "Translation [1, 2]:\n" << m.toString() << "\n" );

            m = matMakeScale<float>( 1, 2 );
            LOG_CHANNEL( "TEST", "Scale [1, 2]:\n" << m.toString() << "\n" );

            m = matMakeRotation<float>( CHESTNUT_PI );
            LOG_CHANNEL( "TEST", "Rotation 180deg:\n" << m.toString() << "\n" );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Transposed/negated/sum/difference/product/scalar product test >>");
        {
            mat3f m1 = matMakeTranslation<float>( 1, 2 );
            mat3f m2 = matMakeScale<float>( 1, 2 );
            mat3f m3;

            LOG_CHANNEL( "TEST", "m1=\n" << m1.toString() << "\n" );
            LOG_CHANNEL( "TEST", "m2=\n" << m2.toString() << "\n" );

            m3 = matTransposed(m1);
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
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_MATRIX3_TEST_H__