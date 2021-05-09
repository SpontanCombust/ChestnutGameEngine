#ifndef __CHESTNUT_VECTOR3_TEST_H__
#define __CHESTNUT_VECTOR3_TEST_H__

#include "engine/maths/vector3.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void vector3Test()
    {
        vec3f v1 = { 2.f, -3.f, 5.5f };
        vec3f v2 = { -6.f, 0.5f, -1.5f };


        LOG_CHANNEL( "TEST", "<<toString test>>" );
        {
            LOG_CHANNEL( "TEST", "v1=" << v1.toString() );
            LOG_CHANNEL( "TEST", "v2=" << v2.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Magnitude test>>" );
        {
            LOG_CHANNEL( "TEST", "mag(v1)=" << vecMagnitude(v1) );
            LOG_CHANNEL( "TEST", "mag(v2)=" << vecMagnitude(v2) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Normalized test>>" );
        {
            vec3f v3 = vecNormalized(v1);
            LOG_CHANNEL( "TEST", "v3=normalized(v1)=" << v3.toString() );
            LOG_CHANNEL( "TEST", "mag(v3)=" << vecMagnitude(v3) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Negated test>>" );
        {
            LOG_CHANNEL( "TEST", "-v1=" << (-v1).toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Sum test>>" );
        {
            vec3f v3 = v1;
            v3 += v2;
            LOG_CHANNEL( "TEST", "v1+v2=" << (v1+v2).toString() );
            LOG_CHANNEL( "TEST", "v1+=v2=" << v3.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Difference test>>" );
        {
            vec3f v3 = v1;
            v3 -= v2;
            LOG_CHANNEL( "TEST", "v1-v2=" << (v1-v2).toString() );
            LOG_CHANNEL( "TEST", "v1-=v2=" << v3.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Scaled test>>" );
        {
            vec3f v3 = v1;
            v3 *= -0.2f;
            LOG_CHANNEL( "TEST", "-0.2 * v1=" << ( -0.2f * v1 ).toString() );  
            LOG_CHANNEL( "TEST", "v1*=-0.2=" << v3.toString() ); 
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Dot product test>>" );
        {
            LOG_CHANNEL( "TEST", "v1 dot v2=" << vecDotProduct( v1, v2 ) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Cross product test>>" );
        {
            LOG_CHANNEL( "TEST", "v1 cross v2=" << vecCrossProduct( v1, v2 ).toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<vec2 cross product test>>" );
        {
            vec2f v3 = vec2f( v1.x(), v1.y() );
            vec2f v4 = vec2f( v2.x(), v2.y() );
            LOG_CHANNEL( "TEST", "(vec2)v1 cross (vec2)v2=" << vecCrossProduct( v3, v4 ).toString() );
        }
        LOG_CHANNEL( "TEST", "" );

    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_VECTOR3_TEST_H__