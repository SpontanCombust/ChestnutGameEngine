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


        LOG_CHANNEL( "TEST", "<<Cast test>>" );
        {
            vec3i v3 = (vec3i)v1;
            LOG_CHANNEL( "TEST", "v3=(vec3i)v1=" << v3.toString() );
            vec3f v4 = (vec3f)v3;
            LOG_CHANNEL( "TEST", "v4=(vec3f)v3=" << v4.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Magnitude test>>" );
        {
            LOG_CHANNEL( "TEST", "mag(v1)=" << vec3Magnitude(v1) );
            LOG_CHANNEL( "TEST", "mag(v2)=" << vec3Magnitude(v2) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Normalized test>>" );
        {
            vec3f v3 = vec3Normalized(v1);
            LOG_CHANNEL( "TEST", "v3=normalized(v1)=" << v3.toString() );
            LOG_CHANNEL( "TEST", "mag(v3)=" << vec3Magnitude(v3) );
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
            LOG_CHANNEL( "TEST", "v1 dot v2=" << vec3DotProduct( v1, v2 ) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Cross product test>>" );
        {
            LOG_CHANNEL( "TEST", "v1 x v2=" << vec3CrossProduct( v1, v2 ).toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<vec2 cross product test>>" );
        {
            LOG_CHANNEL( "TEST", "(vec2)v1 x (vec2)v2=" << vec2CrossProduct( vec3ToVec2(v1), vec3ToVec2(v2) ).toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<vec-cast test>>" );
        {
            vec2f v3 = vec2f(v1);
            vec3f v4 = vec3f(v3);
            LOG_CHANNEL( "TEST", "v3=(vec2)v1=" << v3.toString() );
            LOG_CHANNEL( "TEST", "v4=(vec3)v3=" << v4.toString() );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_VECTOR3_TEST_H__