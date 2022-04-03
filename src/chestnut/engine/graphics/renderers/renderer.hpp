#ifndef __CHESTNUT_ENGINE_RENDERER_H__
#define __CHESTNUT_ENGINE_RENDERER_H__

#include "../../maths/matrix4.hpp"
#include "../opengl/shader_program.hpp"
#include "../opengl/uniform.hpp"
#include "../opengl/framebuffer.hpp"

#include <GL/glew.h>


namespace chestnut::engine
{
    class IRenderer
    {
    protected:
        CShaderProgram m_shader;

        CUniform<mat4f> m_unifView;
        CUniform<mat4f> m_unifProjection;

    public:
        virtual ~IRenderer() = default;

        // Throws ChestnutException on error
        //TODO renderers themselves know which shadere they should use
        void init( std::shared_ptr< CShaderProgramResource > shaderResource );

        void setProjectionMatrix( const mat4f& mat );
        void setViewMatrix( const mat4f& mat );

        // Method called to clear all the data used to render stuff
        virtual void clear() = 0;
        // Method called to render stuff with gathered data to currently bound framebuffer
        virtual void render() = 0;
        // Method called to render stuff with gathered data to a specific framebuffer
        virtual void render( const CFramebuffer& targetFramebuffer ) = 0;


    protected:
        // Set variable locations for view and projection matrices
        virtual bool initProjectionAndViewMatrices();
        // Called on initialization to setup buffers for further use
        virtual bool initBuffers() = 0;
        // called after buffers are initialized
        virtual void onInit() {}
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RENDERER_H__