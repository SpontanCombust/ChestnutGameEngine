#include "maths_tests.hpp"

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
            LOG_CHANNEL( "TEST", "v1=" << vecToString(v1) );
            LOG_CHANNEL( "TEST", "v2=" << vecToString(v2) );
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
            vec2f v3 = vecNormalized(v1);
            LOG_CHANNEL( "TEST", "v3=normalized(v1)=" << vecToString(v3) );
            LOG_CHANNEL( "TEST", "mag(v3)=" << vecMagnitude(v3) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Negated test>>" );
        {
            LOG_CHANNEL( "TEST", "-v1=" << vecToString(-v1) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Sum test>>" );
        {
            vec2f v3 = v1;
            v3 += v2;
            LOG_CHANNEL( "TEST", "v1+v2=" << vecToString(v1 + v2) );
            LOG_CHANNEL( "TEST", "v1+=v2=" << vecToString(v3) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Difference test>>" );
        {
            vec2f v3 = v1;
            v3 -= v2;
            LOG_CHANNEL( "TEST", "v1-v2=" << vecToString(v1-v2) );
            LOG_CHANNEL( "TEST", "v1-=v2=" << vecToString(v3) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Scaled test>>" );
        {
            vec2f v3 = v1;
            v3 *= 0.1f;
            LOG_CHANNEL( "TEST", "0.1 * v1=" << vecToString( 0.1f * v1 ) );   
            LOG_CHANNEL( "TEST", "v1*=0.1=" << vecToString(v3) );   
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Dot product test>>" );
        {
            LOG_CHANNEL( "TEST", "v1 dot v2=" << vecDotProduct( v1, v2 ) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Component product test>>" );
        {
            LOG_CHANNEL( "TEST", "v1 * v2=" << vecToString( v1 * v2 ) );
        }
        LOG_CHANNEL( "TEST", "" );

    }

} // namespace test
    
} // namespace chestnut
