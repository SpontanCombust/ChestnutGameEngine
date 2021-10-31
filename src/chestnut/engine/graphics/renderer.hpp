#ifndef __CHESTNUT_ENGINE_RENDERER_H__
#define __CHESTNUT_ENGINE_RENDERER_H__

#include "shader_program.hpp"
#include "../maths/matrix4.hpp"
#include "framebuffer.hpp"

#include <GL/glew.h>

namespace chestnut::engine
{
    class IRenderer
    {
    protected:
        CShaderProgram m_shader;

        GLint m_unifViewLoc;
        GLint m_unifProjectionLoc;

    public:
        virtual ~IRenderer();

        // Throws exception on error
        void init( const CShaderProgram& shader );

        void bindShader();
        void unbindShader();

        // requires bound renderer shader
        void setProjectionMatrix( const mat4f& mat );
        // requires bound renderer shader
        void setViewMatrix( const mat4f& mat );

        // Method called to clear all the data used to render stuff
        virtual void clear() = 0;
        // Method called to render stuff with gathered data to currently bound framebuffer
        virtual void render() = 0;
        // Method called to render stuff with gathered data to a specific framebuffer
        virtual void render( const CFramebuffer& targetFramebuffer ) = 0;


    protected:
        virtual void onInit() = 0;
        // Set variable locations for view and projection matrices
        virtual bool setProjectionAndViewMatrixLocations();
        // Called on initialization to fetch custom shader variables' locations
        virtual bool setShaderVariableLocations() = 0;
        // Called on initialization to setup buffers for further use
        virtual void initBuffers() = 0;
        // Called on renderer destruction
        virtual void deleteBuffers() {};
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RENDERER_H__