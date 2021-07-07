#include "maths_tests.hpp"

#include "engine/maths/vector.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void vectorNTest()
    {
        Vector<float,1> v1 = {2};
        vec2f v2 = { 2, 3 };
        Vector<float,5> v5_1 = {4}; v5_1.elements[4] = 5;
        Vector<float,5> v5_2 = {7}; v5_2.elements[0] = 6;

        LOG_CHANNEL( "TEST", "<<toString test>>" );
        {
            LOG_CHANNEL( "TEST", "v1=" << vecToString(v1) );
            LOG_CHANNEL( "TEST", "v2=" << vecToString(v2) );
            LOG_CHANNEL( "TEST", "v5_1=" << vecToString(v5_1) );
            LOG_CHANNEL( "TEST", "v5_2=" << vecToString(v5_2) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Sum test>>" );
        {
            Vector<float,5> sum = v5_1;
            sum += v5_2;
            LOG_CHANNEL( "TEST", "v5_1+v5_2=" << vecToString(v5_1+v5_2) );
            LOG_CHANNEL( "TEST", "v5_1+=v5_2=" << vecToString(sum) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Component product test>>" );
        {
            LOG_CHANNEL( "TEST", "v1 * v1=" << vecToString( v1 * v1 ) );
            LOG_CHANNEL( "TEST", "v5_1 * v5_2=" << vecToString( v5_1 * v5_2 ) );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut
