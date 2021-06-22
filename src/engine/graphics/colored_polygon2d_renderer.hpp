#ifndef __CHESTNUT_COLORED_POLYGON_RENDERER_H__
#define __CHESTNUT_COLORED_POLYGON_RENDERER_H__

#include "renderer.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/maths/vector4.hpp"
#include "colored_polygon2d.hpp"

#include <vector>

namespace chestnut
{
    struct SColoredPolygon2DRender_Vertex
    {
        vec2f position;
        vec4f color;
        vec2f origin;
        vec2f translation;
        vec2f scale;
        float rotation;
    };

    class CColoredPolygon2DRenderer : public IRenderer
    {
    private:
        std::vector< SColoredPolygon2DRender_Vertex > m_vecColoredVertices;
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

    public:
        // requires bound renderer shader
        void reserveBufferSpace( GLsizei targetPolygonVertexCapacity, GLsizei targetVertexIndexCapacity );

        void clear() override;

        void submitPolygon( const CColoredPolygon2D& polygon, const vec2f& translation, const vec2f& origin = { 0.f, 0.f }, const vec2f& scale = { 1.f, 1.f }, float rotation = 0.f );
        // requires bound renderer shader
        void render() override;

    private:
        bool onInitCustom() override;

        bool setShaderVariableLocations() override;

        void initBuffers() override;

        void prepareBuffers();

        void deleteBuffers() override;
    };

} // namespace chestnut


#endif // __CHESTNUT_COLORED_POLYGON_RENDERER_H__