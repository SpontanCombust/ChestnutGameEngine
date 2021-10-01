#include "renderer.hpp"

#include "../misc/exception.hpp"

namespace chestnut::engine
{    
    void IRenderer::init( const CShaderProgram& shader ) 
    {
        m_shader = shader;
        if( !m_shader.isValid() )
        {
            throw ChestnutException( "Invalid shader program passed to the renderer!" );
        }

        m_shader.bind();
        if( !setProjectionAndViewMatrixLocations() )
        {
            throw ChestnutException( "Failed to set shader locations for projection and view matrice uniforms!" );
        }
        if( !setShaderVariableLocations() )
        {
            throw ChestnutException( "Failed to set shader locations for attributes and/or uniforms!" );
        }

        initBuffers();

        onInit();
    }

    IRenderer::~IRenderer() 
    {
        deleteBuffers();
    }

    void IRenderer::bindShader() 
    {
        m_shader.bind();
    }

    void IRenderer::unbindShader() 
    {
        m_shader.unbind();
    }

    bool IRenderer::setProjectionAndViewMatrixLocations() 
    {
        m_unifViewLoc       = m_shader.getUniformLocation( "uView" );
        m_unifProjectionLoc = m_shader.getUniformLocation( "uProjection" );

        if( m_unifViewLoc == -1 || m_unifProjectionLoc  == -1 )
        {
            return false;
        }
        return true;
    }

    void IRenderer::setProjectionMatrix( const mat4f& mat ) 
    {
        m_shader.setMatrix4f( m_unifProjectionLoc, mat );
    }

    void IRenderer::setViewMatrix( const mat4f& mat ) 
    {
        m_shader.setMatrix4f( m_unifViewLoc, mat );
    }

} // namespace chesntut
