#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/renderers/renderer.hpp"
#include "chestnut/engine/graphics/text.hpp"
#include "chestnut/engine/graphics/opengl/buffer.hpp"
#include "chestnut/engine/graphics/opengl/vertex_array.hpp"

#include <vector>

namespace chestnut::engine
{
    /**
     * @brief A renderer class responsible for rendering formatted text
     * 
     * @details
     * Renderer receives data with submitText() method, which takes:
     * - text object (stores texture, position and color information about glyphs)
     * - translation vector
     * - scale vector
     * 
     * Received data is transformed into vertices, which in turn get grouped.
     * For every glyph in the text 4 vertices are created, each with:
     * - RGB color vector
     * - position vector (relative to the text)
     * - uv vector (texture coordinates on the texture sheet where given glyph resides)
     * - translation vector
     * - scale vector
     * Grouping of these vertices is based on which texture the glyph belongs to.
     * 
     * The connection between a glyph and a texture exists in its font resource.
     * For every font size and style a texture sheet is generated, which stores 
     * all necessary glyphs in this one texture in different places (that's why UV coordinates are also important).
     * So to fetch a specific glyph subtexture both a texture ID and clipping rectangle is needed by the renderer.
     * A single text can have glyphs that refer to all sorts of different textures, but this grouping is done only
     * in the scope of a single text object and not accross all submitted ones. It is done this way to avoid
     * inconsistent layering between texts i.e. if for example 2 texts get submitted and one may obscure another,
     * even if they have some glyphs that correspond to the same texture there will still be a hard order as to which
     * glyph will be rendered last based on text submition order and not texture ID sorting order.
     * 
     * At the rendering stage data stored with vertex groups gets sent to the GPU to a single vertex and element buffer
     * and batch structs are created, which store information as to how this sent data is layed out.
     * Batches consist of texture ID (essentially a batch is made for every vertex group), element/index count and 
     * element/index offset. During rendering for every batch first a texture is bound and then text is drawn using
     * element/index count and offset in the buffer. 
     */
    class CHESTNUT_API CTextRenderer : public IRenderer
    {
        struct STextRender_Vertex
        {
            vec3f color;
            vec2f pos;
            vec2f uv;
            vec2f translation;
            vec2f scale;
        };

        struct STextRender_VertexGroup
        {
            GLuint texID;
            std::vector< STextRender_Vertex > vecVertices;
        };

        struct STextRender_Batch
        {
            GLuint texID;
            GLsizei elementCount;
            GLint elementOffset;
        };


    private:
        std::vector< STextRender_VertexGroup > m_vecVertexGroups;
        std::vector< STextRender_Batch > m_vecBatches;

        CVertexArray m_vao;
        std::shared_ptr<CBuffer> m_vbo;
        std::shared_ptr<CBuffer> m_ibo;

        GLsizei m_glyphCapacity;


    public:
        void reserveBufferSpace( GLsizei targetGlyphCapacity );

        void clear() override;

        void submitText( const CText& text, vec2f translation, vec2f scale = { 1.f, 1.f } );

        void render() override;

        void render( const CFramebuffer& targetFramebuffer ) override;


    private:
        bool setShaderProgram() override;
        bool initBuffers() override;
        void onInit() override;

        void prepareBuffers();
    };
    
} // namespace chestnut::engine

