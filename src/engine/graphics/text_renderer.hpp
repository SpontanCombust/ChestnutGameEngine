#ifndef __CHESTNUT_TEXT_RENDERER_H__
#define __CHESTNUT_TEXT_RENDERER_H__

#include "text.hpp"
#include "shader_program.hpp"

#include <vector>

namespace chestnut
{
    class CTextRenderer
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
        CShaderProgram m_shader;

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

        GLint m_unifProjectionLoc;
        GLint m_unifViewLoc;

    public:
        CTextRenderer( const CShaderProgram& shader );
        ~CTextRenderer();

        void bindShader();
        void unbindShader();

        void reserveBufferSpace( GLsizei targetGlyphCapacity );

        // requires bound renderer shader
        void setProjectionMatrix( mat4f projection );
        // requires bound renderer shader
        void setViewMatrix( mat4f view );

        void clear();

        void submitText( const CText& text, vec2f translation, vec2f scale = { 1.f, 1.f } );

        // requires bound renderer shader
        void render();

    private:
        void initBuffers();

        bool setShaderVariableNames( const std::string& attrVertPos,
                                     const std::string& attrVertUV,
                                     const std::string& attrVertColor,
                                     const std::string& attrVertTranslation,
                                     const std::string& attrVertScale,
                                     const std::string& unifProjection,
                                     const std::string& unifView );

        void makeBatches();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_TEXT_RENDERER_H__