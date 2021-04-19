#ifndef __CHESTNUT_VECTOR2_TEST_H__
#define __CHESTNUT_VECTOR2_TEST_H__

#include "engine/maths/vector2.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void vector2Test()
    {
        vec2f v1 = { 2.f, -3.f };
        vec2f v2 = { -6.f, 0.5f };


        LOG_CHANNEL( "TEST", "<<toString test>>" );
        {
            LOG_CHANNEL( "TEST", "v1=" << v1.toString() );
            LOG_CHANNEL( "TEST", "v2=" << v2.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Cast test>>" );
        {
            vec2i v3 = (vec2i)v1;
            LOG_CHANNEL( "TEST", "v3=(vec2i)v1=" << v3.toString() );
            vec2f v4 = (vec2f)v3;
            LOG_CHANNEL( "TEST", "v4=(vec2f)v3=" << v4.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Magnitude test>>" );
        {
            LOG_CHANNEL( "TEST", "mag(v1)=" << vec2Magnitude(v1) );
            LOG_CHANNEL( "TEST", "mag(v2)=" << vec2Magnitude(v2) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Normalized test>>" );
        {
            vec2f v3 = vec2Normalized(v1);
            LOG_CHANNEL( "TEST", "v3=normalized(v1)=" << v3.toString() );
            LOG_CHANNEL( "TEST", "mag(v3)=" << vec2Magnitude(v3) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Negated test>>" );
        {
            LOG_CHANNEL( "TEST", "-v1=" << (-v1).toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Sum test>>" );
        {
            vec2f v3 = v1;
            v3 += v2;
            LOG_CHANNEL( "TEST", "v1+v2=" << (v1+v2).toString() );
            LOG_CHANNEL( "TEST", "v1+=v2=" << v3.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Difference test>>" );
        {
            vec2f v3 = v1;
            v3 -= v2;
            LOG_CHANNEL( "TEST", "v1-v2=" << (v1-v2).toString() );
            LOG_CHANNEL( "TEST", "v1-=v2=" << v3.toString() );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Scaled test>>" );
        {
            vec2f v3 = v1;
            v3 *= 0.1f;
            LOG_CHANNEL( "TEST", "0.1 * v1=" << ( 0.1f * v1 ).toString() );   
            LOG_CHANNEL( "TEST", "v1*=0.1=" << v3.toString() );   
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Dot product test>>" );
        {
            LOG_CHANNEL( "TEST", "v1 dot v2=" << vec2DotProduct( v1, v2 ) );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test
    
} // namespace chestnut

#endif // __CHESTNUT_VECTOR2_TEST_H__