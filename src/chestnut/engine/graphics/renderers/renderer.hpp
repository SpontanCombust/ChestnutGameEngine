#pragma once


#include "chestnut/engine/macros.hpp"
#include "../../maths/matrix4.hpp"
#include "../opengl/shader_program.hpp"
#include "../opengl/uniform.hpp"
#include "../opengl/framebuffer.hpp"

#include <GL/glew.h>


namespace chestnut::engine
{
    class CHESTNUT_API IRenderer
    {
    protected:
        CShaderProgram m_shader;

        CUniform<mat4f> m_unifView;
        CUniform<mat4f> m_unifProjection;

    public:
        virtual ~IRenderer() = default;

        // Throws ChestnutException on error
        // This method is here because we want to call virtual methods on initialization 
        // and that shouldn't be done in the constructor
        void init();

        void setProjectionMatrix( const mat4f& mat );
        void setViewMatrix( const mat4f& mat );

        // Method called to clear all the data used to render stuff
        virtual void clear() = 0;
        // Method called to render stuff with gathered data to currently bound framebuffer
        virtual void render() = 0;
        // Method called to render stuff with gathered data to a specific framebuffer
        virtual void render( const CFramebuffer& targetFramebuffer ) = 0;


    protected:
        virtual bool setShaderProgram() = 0;
        // Set variable locations for view and projection matrices
        virtual bool initProjectionAndViewMatrices();
        // Called on initialization to setup buffers for further use
        virtual bool initBuffers() = 0;
        // called after buffers are initialized
        virtual void onInit() {}
    };

} // namespace chestnut::engine

