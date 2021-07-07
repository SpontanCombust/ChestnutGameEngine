#include "maths_tests.hpp"

#include "engine/constants.hpp"
#include "engine/maths/vector_transform.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void vectorTransformTest()
    {
        vec2f v1 = { 2.f, -3.f };
        vec3f v2 = { -6.f, 0.5f, -1.5f };
        vec4f v3 = { 0.f, 2.0f, -1.f, 1.f };

        LOG_CHANNEL( "TEST", "<<toString test>>" );
        {
            LOG_CHANNEL( "TEST", "v1=" << vecToString(v1) );
            LOG_CHANNEL( "TEST", "v2=" << vecToString(v2) );
            LOG_CHANNEL( "TEST", "v3=" << vecToString(v3) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Multiply vector by matrix test >>");
        {
            vec3f v1 = { -1, 4, 0 };
            vec4f v2 = { -1, 0, 4, 1 };
            mat3f m1 = matMakeRotation<float>( CHESTNUT_PI );
            mat4f m2 = matMakeRotation<float>( { 0, 0, 1 }, CHESTNUT_PI );

            LOG_CHANNEL( "TEST", "v1=" << vecToString(v1) );
            LOG_CHANNEL( "TEST", "m1=\n" << matToString(m1) );

            LOG_CHANNEL( "TEST", "m1*v1=" << vecToString( m1 * v1 ) );

            LOG_CHANNEL( "TEST", "" );
            
            LOG_CHANNEL( "TEST", "v2=" << vecToString(v2) );
            LOG_CHANNEL( "TEST", "m2=\n" << matToString(m2) );

            LOG_CHANNEL( "TEST", "m2*v2=" << vecToString( m2 * v2 ) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Multiply vector by matrix different size test >>");
        {
            vec3f v3 = { -1, 4, 0 };
            mat4f m4 = matMakeRotation<float>( { 0, 0, 1 }, CHESTNUT_PI );

            LOG_CHANNEL( "TEST", "v3=" << vecToString(v3) );
            LOG_CHANNEL( "TEST", "m4=\n" << matToString(m4) );

            LOG_CHANNEL( "TEST", "m4*v3=" << vecToString( m4 * v3 ) );

            // vec4f v4 = { 1, 2, 3, 4 };
            // mat3f m3 = matMakeTranslation<float>( 1.f, 2.f );
            // LOG_CHANNEL( "TEST", "m3*v4=" << matToString( m3 * v4 ) ); // compiler error
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<vec2 transform test>>" );
        {
            vecTranslate( v1, 1.f, 2.f );
            LOG_CHANNEL( "TEST", "T(1,2)(v1)=" << vecToString(v1) );
            vecScale( v1, 3.f, 4.f );
            LOG_CHANNEL( "TEST", "S(3,4)(v1)=" << vecToString(v1) );
            vecRotate( v1, CHESTNUT_PI );
            LOG_CHANNEL( "TEST", "R(PI)(v1)=" << vecToString(v1) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<vec3 transform test>>" );
        {
            vecTranslate( v2, 1.f, 2.f, 3.f );
            LOG_CHANNEL( "TEST", "T(1,2,3)(v2)=" << vecToString(v2) );
            vecScale( v2, 4.f, 5.f, 6.f );
            LOG_CHANNEL( "TEST", "S(4,5,6)(v2)=" << vecToString(v2) );
            vecRotate( v2, { 0, 0, 1 }, CHESTNUT_PI );
            LOG_CHANNEL( "TEST", "Rz(PI)(v2)=" << vecToString(v2) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<vec4 transform test>>" );
        {
            vecTranslate( v3, 1.f, 2.f, 3.f );
            LOG_CHANNEL( "TEST", "T(1,2,3)(v3)=" << vecToString(v3) );
            vecScale( v3, 4.f, 5.f, 6.f );
            LOG_CHANNEL( "TEST", "S(4,5,6)(v3)=" << vecToString(v3) );
            vecRotate( v3, { 0, 0, 1 }, CHESTNUT_PI );
            LOG_CHANNEL( "TEST", "Rz(PI)(v3)=" << vecToString(v3) );
        }
        LOG_CHANNEL( "TEST", "" );

    }

} // namespace test

} // namespace chestnut
