#ifndef __CHESTNUT_COLORED_POLYGON_RENDERER_H__
#define __CHESTNUT_COLORED_POLYGON_RENDERER_H__

#include "engine/libs.hpp"
#include "shader_program.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/maths/vector4.hpp"
#include "engine/maths/matrix4.hpp"
#include "colored_polygon2d.hpp"

#include <vector>

namespace chestnut
{
    struct SColoredVertex
    {
        vec2f position;
        vec4f color;
        vec2f origin;
        vec2f translation;
        vec2f scale;
        float rotation;
    };

    class CColoredPolygon2DRenderer
    {
    private:
        CShaderProgram m_shader;

        std::vector< SColoredVertex > m_vecColoredVertices;
        std::vector< GLuint > m_vecIndices;

        GLuint m_vbo;
        GLuint m_ebo;
        GLuint m_vao;

        GLsizei m_polygonVertexCapacity;
        GLsizei m_vertexIndexCapacity;

        GLint m_attrVertPosLoc;
        GLint m_attrVertColorLoc;
        GLint m_attrVertOriginLoc;
        GLint m_attrVertTranslLoc;
        GLint m_attrVertScaleLoc;
        GLint m_attrVertRotLoc;

        GLint m_unifViewLoc;
        GLint m_unifProjectionLoc;

    public:
        CColoredPolygon2DRenderer( const CShaderProgram& shader );
        ~CColoredPolygon2DRenderer();

        void bindShader();
        void unbindShader();
        
        // requires bound renderer shader
        void setProjectionMatrix( const mat4f& mat );
        // requires bound renderer shader
        void setViewMatrix( const mat4f& mat );
        // requires bound renderer shader
        void reserveBufferSpace( GLsizei targetPolygonVertexCapacity, GLsizei targetVertexIndexCapacity );

        void clear();

        void submitPolygon( const CColoredPolygon2D& polygon, const vec2f& translation, const vec2f& origin = { 0.f, 0.f }, const vec2f& scale = { 1.f, 1.f }, float rotation = 0.f );
        // requires bound renderer shader
        void render();

    private:
        bool setShaderVariableNames( const std::string& attrVertPos,
                                     const std::string& attrVertColor,
                                     const std::string& attrVertOrigin,
                                     const std::string& attrVertTransl,
                                     const std::string& attrVertScale,
                                     const std::string& attrVertRot,
                                     const std::string& unifView,
                                     const std::string& unifProjection );

        void initBuffers();

        void prepareBuffers();
    };

} // namespace chestnut


#endif // __CHESTNUT_COLORED_POLYGON_RENDERER_H__