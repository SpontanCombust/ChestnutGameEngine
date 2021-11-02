#include "shader_program.hpp"

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

    GLint CShaderProgram::getAttributeLocation( const char *attrName ) 
    {
        if( m_shaderResource )
        {
            return m_shaderResource->getAttributeLocation( attrName );
        }

        return -1;
    }

    GLint CShaderProgram::getUniformLocation( const char *uniformName ) 
    {
        if( m_shaderResource )
        {
            return m_shaderResource->getUniformLocation( uniformName );
        }
        
        return -1;
    }

    bool CShaderProgram::setInt( const char *unifName, int val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform1i( loc, val );
            return true;
        }

        return false;
    }

    bool CShaderProgram::setVector2f( const char *unifName, const vec2f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform2fv( loc, 1, val.data() );
            return true;
        }

        return false;
    }

    bool CShaderProgram::setVector3f( const char *unifName, const vec3f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform3fv( loc, 1, val.data() );
            return true;
        }
        
        return false;
    }

    bool CShaderProgram::setVector4f( const char *unifName, const vec4f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniform4fv( loc, 1, val.data() );
            return true;
        }
        
        return false;
    }

    bool CShaderProgram::setMatrix3f( const char *unifName, const mat3f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniformMatrix3fv( loc, 1, GL_FALSE, val.data() );
            return true;
        }
        
        return false;
    }

    bool CShaderProgram::setMatrix4f( const char *unifName, const mat4f& val ) 
    {
        GLint loc = getUniformLocation( unifName );
        if( loc != -1 )
        {
            glUniformMatrix4fv( loc, 1, GL_FALSE, val.data() ); 
            return true;  
        }
        
        return false;
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

} // namespace chestnut::engine
