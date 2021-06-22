#ifndef __CHESTNUT_VECTOR_CAST_TEST_H__
#define __CHESTNUT_VECTOR_CAST_TEST_H__

#include "engine/maths/vector_cast.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void vectorCastTest()
    {
        LOG_CHANNEL( "TEST", "<< Size cast test >>" );
        {
            vec2f v2 { 2.f, 3.f };
            vec3f v3 { 4.f, 5.f, 6.f };

            LOG_CHANNEL( "TEST", "vec2=" + vecToString(v2) );
            LOG_CHANNEL( "TEST", "vec3=" + vecToString(v3) );
            LOG_CHANNEL( "TEST", "vec2 to vec3: " + vecToString( vecCastSizeGreater<3>(v2) ) );
            LOG_CHANNEL( "TEST", "vec3 to vec2: " + vecToString( vecCastSizeSmaller<2>(v3) ) );
            // LOG_CHANNEL( "TEST", "vec2 to vec3: " + vecToString( vecCastSizeGreater<3>(v3) ) ); // compile error
            LOG_CHANNEL( "TEST", "vec2 to vec3: " + vecToString( vecCastSize<3>(v2,0.f) ) );
            LOG_CHANNEL( "TEST", "vec3 to vec2: " + vecToString( vecCastSize<2>(v3) ) );
            LOG_CHANNEL( "TEST", "vec3 to vec3: " + vecToString( vecCastSize<3>(v3) ) );
        }
        LOG_CHANNEL( "TEST", "" );

        LOG_CHANNEL( "TEST", "<< Type cast test >>" );
        {
            vec2i vi { 2, 3 };
            vec2f vf { 4.4f, 1.9f };

            LOG_CHANNEL( "TEST", "vec2i=" + vecToString(vi) );
            LOG_CHANNEL( "TEST", "vec2f=" + vecToString(vf) );
            LOG_CHANNEL( "TEST", "vec2i to vec2f: " + vecToString( vecCastType<float>(vi) ) );
            LOG_CHANNEL( "TEST", "vec2f to vec2i: " + vecToString( vecCastType<int>(vf) ) );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_VECTOR_CAST_TEST_H__