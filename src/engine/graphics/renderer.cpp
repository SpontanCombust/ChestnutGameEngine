#include "renderer.hpp"

#include "../debug/debug.hpp"

#include <cassert>

namespace chestnut
{    
    void IRenderer::init( const CShaderProgram& shader ) 
    {
        m_shader = shader;
        assert( m_shader.isValid() );

        m_shader.bind();
        assert( setProjectionAndViewMatrixLocations() );
        assert( setShaderVariableLocations() );
        initBuffers();

        assert( onInitCustom() );
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
