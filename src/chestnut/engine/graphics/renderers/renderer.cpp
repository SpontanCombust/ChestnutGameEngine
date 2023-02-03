#include "chestnut/engine/graphics/renderers/renderer.hpp"

#include "chestnut/engine/misc/exception.hpp"

namespace chestnut::engine
{    
    void IRenderer::init() 
    {
        //TODO this can be simply made as a function that returns the tl::expected of shader resource
        if( !setShaderProgram() )
        {
            throw ChestnutException( "Failed to set renderer shader!" );
        }

        m_shader.bind();

        if( !initProjectionAndViewMatrices() )
        {
            throw ChestnutException( "Failed to set shader locations for projection and view matrice uniforms!" );
        }

        // Initialize matrices
        setViewMatrix(mat4f());
        setProjectionMatrix(mat4f());

        if( !initBuffers() )
        {
            throw ChestnutException( "Failed to initialize buffers!" );
        }

        onInit();
    }

    bool IRenderer::initProjectionAndViewMatrices() 
    {
        try
        {
            m_unifView = m_shader.getUniform<mat4f>( "uView" ).value();
            m_unifProjection = m_shader.getUniform<mat4f>( "uProjection" ).value();
        }
        catch(const tl::bad_optional_access& e)
        {
            return false;
        }
       
        return true;
    }

    void IRenderer::setProjectionMatrix( const mat4f& mat ) 
    {
        m_unifProjection.set(mat);
    }

    void IRenderer::setViewMatrix( const mat4f& mat ) 
    {
        m_unifView.set(mat);
    }

} // namespace chesntut
