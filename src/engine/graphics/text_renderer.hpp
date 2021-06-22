#ifndef __CHESTNUT_TEXT_RENDERER_H__
#define __CHESTNUT_TEXT_RENDERER_H__

#include "renderer.hpp"
#include "text.hpp"

#include <vector>

namespace chestnut
{
    class CTextRenderer : public IRenderer
    {
        struct STextRender_Vertex
        {
            vec2f pos;
            vec2f uv;
            vec4f color;
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

        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_ebo;

        GLsizei m_glyphCapacity;

        GLint m_attrVertPosLoc;
        GLint m_attrVertUVLoc;
        GLint m_attrVertColorLoc;
        GLint m_attrVertTranslationLoc;
        GLint m_attrVertScaleLoc;

    public:
        void reserveBufferSpace( GLsizei targetGlyphCapacity );

        void clear() override;

        void submitText( const CText& text, vec2f translation, vec2f scale = { 1.f, 1.f } );

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

#endif // __CHESTNUT_TEXT_RENDERER_H__