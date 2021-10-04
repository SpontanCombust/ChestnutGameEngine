#ifndef __CHESTNUT_ENGINE_COLORED_POLYGON2D_RENDERER_H__
#define __CHESTNUT_ENGINE_COLORED_POLYGON2D_RENDERER_H__

#include "renderer.hpp"
#include "colored_polygon2d.hpp"

#include <unordered_map>
#include <vector>

namespace chestnut::engine
{
    /**
     * @brief A renderer class used to render plain polygons in 2D space
     * 
     * @details
     * Renderer receives data with submitPolygon() method, which takes in:
     * - CColoredPolygon2D object (which stores indices and normalized vertices),
     * - translation vector (where polygon should be moved),
     * - scale vector (how big the polygon should be relative to its original dimensions) 
     * - rotation in radians.
     * Indices received from polygon object are appropriately offset to be able to store them at once with all other indices.
     * 
     * The received data is converted into structs representing rendering vertices. This conversion is straightforward as every render vertex corresponds
     * to one of vertices retrieved from polygon during submition stage.
     * Render instance stores:
     * - position vector (original normalized vertex coordinate supplied by the polygon),
     * - RGBA color vector,
     * - translation vector,
     * - scale vector,
     * - rotation value.
     * 
     * The rendering stage doesn't attempt to optimize stored data any more. All vertices and indices are sent to the GPU as they are
     * in a single vertex and element buffer.
     * All is simply drawn at once using these indices.
     */
    class CColoredPolygon2DRenderer : public IRenderer
    {
        struct SColoredPolygon2DRender_Vertex
        {
            vec2f position;
            vec4f color;
            vec2f translation;
            vec2f scale;
            float rotation;
        };

        struct SColoredPolygon2DRender_VertexGroup
        {
            std::vector< SColoredPolygon2DRender_Vertex > vecRenderVertices;
            std::vector< GLuint > vecRenderIndices;
        };

        struct SColoredPolygon2DRender_Batch
        {
            GLenum drawMode;
            GLsizei indexCount;
            GLsizei indexOffset;
        };
        
    private:
        std::unordered_map< GLenum, SColoredPolygon2DRender_VertexGroup > m_mapDrawModeToVertexGroup;
        std::vector< SColoredPolygon2DRender_Batch > m_vecBatches;

        GLuint m_vbo;
        GLuint m_ebo;
        GLuint m_vao;

        GLsizei m_polygonVertexCapacity;
        GLsizei m_vertexIndexCapacity;

        GLint m_attrVertPosLoc;
        GLint m_attrVertColorLoc;
        GLint m_attrVertTranslLoc;
        GLint m_attrVertScaleLoc;
        GLint m_attrVertRotLoc;

    public:
        // requires bound renderer shader
        void reserveBufferSpace( GLsizei targetPolygonVertexCapacity, GLsizei targetVertexIndexCapacity );

        void clear() override;

        void submitPolygon( const SColoredPolygon2D& polygonModel, const vec2f& translation, const vec2f& scale = { 1.f, 1.f }, float rotation = 0.f );
        
        void submitPolygon( const SMulticoloredPolygon2D& polygonModel, const vec2f& translation, const vec2f& scale = { 1.f, 1.f }, float rotation = 0.f );

        // requires bound renderer shader
        void render() override;

    private:
        void onInit() override;

        bool setShaderVariableLocations() override;

        void initBuffers() override;

        void prepareBuffers();

        void deleteBuffers() override;
    };

} // namespace chestnut::engine


#endif // __CHESTNUT_ENGINE_COLORED_POLYGON2D_RENDERER_H__