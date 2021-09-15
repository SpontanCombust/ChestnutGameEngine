#include "shader_program.hpp"

#include "../debug/debug.hpp"

namespace chestnut
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
        return m_shaderResource->m_programID;
    }

    bool CShaderProgram::isValid() const
    {
        if( m_shaderResource && m_shaderResource->isValid() )
        {
            return true;
        }
        return false;
    }

    void CShaderProgram::bind()
    {
        glUseProgram( m_shaderResource->m_programID );
    }

    void CShaderProgram::unbind()
    {
        glUseProgram(0);
    }

    GLint CShaderProgram::getAttributeLocation( std::string attrName ) 
    {
        return m_shaderResource->getAttributeLocation( attrName );
    }

    GLint CShaderProgram::getUniformLocation( std::string uniformName ) 
    {
        return m_shaderResource->getUniformLocation( uniformName );
    }

    bool CShaderProgram::setInt( const std::string& unifName, int val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform1i( loc, val );
            return true;
        }
        else
        {
            return false;
        }
    }

    bool CShaderProgram::setVector2f( const std::string& unifName, const vec2f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform2fv( loc, 1, val.data() );
            return true;
        }
        else
        {
            return false;
        }
    }

    bool CShaderProgram::setVector3f( const std::string& unifName, const vec3f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform3fv( loc, 1, val.data() );
            return true;
        }
        else
        {
            return false;
        }
    }

    bool CShaderProgram::setVector4f( const std::string& unifName, const vec4f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform4fv( loc, 1, val.data() );
            return true;
        }
        else
        {
            return false;
        }
    }

    bool CShaderProgram::setMatrix3f( const std::string& unifName, const mat3f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniformMatrix3fv( loc, 1, GL_FALSE, val.data() );
            return true;
        }
        else
        {
            return false;
        }
    }

    bool CShaderProgram::setMatrix4f( const std::string& unifName, const mat4f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniformMatrix4fv( loc, 1, GL_FALSE, val.data() ); 
            return true;  
        }
        else
        {
            return false;
        }
    }

    void CShaderProgram::setInt( GLint loc, GLint val ) 
    {
        glUniform1i( loc, val );
    }

    void CShaderProgram::setVector2f( GLint loc, const vec2f& val ) 
    {
        glUniform2fv( loc, 1, val.data() );
    }

    void CShaderProgram::setVector3f( GLint loc, const vec3f& val ) 
    {
        glUniform3fv( loc, 1, val.data() );
    }

    void CShaderProgram::setVector4f( GLint loc, const vec4f& val ) 
    {
        glUniform4fv( loc, 1, val.data() );
    }

    void CShaderProgram::setMatrix3f( GLint loc, const mat3f& val ) 
    {
        glUniformMatrix3fv( loc, 1, GL_FALSE, val.data() );
    }

    void CShaderProgram::setMatrix4f( GLint loc, const mat4f& val ) 
    {
        glUniformMatrix4fv( loc, 1, GL_FALSE, val.data() );
    }

} // namespace chestnut
