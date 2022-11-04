#include "chestnut/engine/graphics/opengl/shader_program.hpp"

namespace chestnut::engine
{
    CShaderProgram::CShaderProgram( std::shared_ptr<CShaderProgramResource> resource ) 
    {
        m_shaderResource = resource;
    }

    const std::shared_ptr<CShaderProgramResource>& CShaderProgram::getResource() const
    {
        return m_shaderResource;
    }

    GLuint CShaderProgram::getID() const
    {
        if( m_shaderResource )
        {
            return m_shaderResource->m_programID;
        }

        return 0;
    }

    bool CShaderProgram::isValid() const
    {
        if( m_shaderResource )
        {
            return true;
        }

        return false;
    }

    void CShaderProgram::bind()
    {
        if( m_shaderResource )
        {
            glUseProgram( m_shaderResource->m_programID );
        }
    }

    void CShaderProgram::unbind()
    {
        glUseProgram(0);
    }

} // namespace chestnut::engine
