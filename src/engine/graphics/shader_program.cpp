#include "shader_program.hpp"

#include "engine/libs.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
    CShaderProgram::CShaderProgram( std::shared_ptr<CShaderProgramResource> resource ) 
    {
        m_shaderResource = resource;
    }

    GLuint CShaderProgram::getID() const
    {
        return m_shaderResource->programID;
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
        glUseProgram( m_shaderResource->programID );
    }

    void CShaderProgram::unbind()
    {
        glUseProgram(0);
    }

    GLint CShaderProgram::getAttributeLocation( std::string attrName ) 
    {
        GLint loc;
        auto& attrMap = m_shaderResource->mapAttributeNameToLocation;

        if( attrMap.find( attrName ) != attrMap.end() )
        {
            loc = attrMap[ attrName ];
        }
        else
        {
            loc = glGetAttribLocation( m_shaderResource->programID, attrName.c_str() );

            if( loc == -1 )
            {
                LOG_CHANNEL( "SHADER_PROGRAM", "Couldn't find attribute with name " << attrName << " in program " << m_shaderResource->programID );
            }
            else
            {
                attrMap[ attrName ] = loc;   
            }
        }

        return loc;
    }

    GLint CShaderProgram::getUniformLocation( std::string uniformName ) 
    {
        GLint loc;
        auto& unifMap = m_shaderResource->mapUniformNameToLocation;

        if( unifMap.find( uniformName ) != unifMap.end() )
        {
            loc = unifMap[ uniformName ];
        }
        else
        {
            loc = glGetUniformLocation( m_shaderResource->programID, uniformName.c_str() );

            if( loc == -1 )
            {
                LOG_CHANNEL( "SHADER_PROGRAM", "Couldn't find uniform with name " << uniformName << " in program " << m_shaderResource->programID );
            }
            else
            {
                unifMap[ uniformName ] = loc;   
            }
        }
        
        return loc;
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
            glUniform2fv( loc, 1, val.data );
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
            glUniform3fv( loc, 1, val.data );
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
            glUniform4fv( loc, 1, val.data );
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
            glUniformMatrix3fv( loc, 1, GL_FALSE, val.data );
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
            glUniformMatrix4fv( loc, 1, GL_FALSE, val.data ); 
            return true;  
        }
        else
        {
            return false;
        }
    }

    void CShaderProgram::setInt( GLint loc, int val ) 
    {
        glUniform1i( loc, val );
    }

    void CShaderProgram::setVector2f( GLint loc, const vec2f& val ) 
    {
        glUniform2fv( loc, 1, val.data );
    }

    void CShaderProgram::setVector3f( GLint loc, const vec3f& val ) 
    {
        glUniform3fv( loc, 1, val.data );
    }

    void CShaderProgram::setVector4f( GLint loc, const vec4f& val ) 
    {
        glUniform4fv( loc, 1, val.data );
    }

    void CShaderProgram::setMatrix3f( GLint loc, const mat3f& val ) 
    {
        glUniformMatrix3fv( loc, 1, GL_FALSE, val.data );
    }

    void CShaderProgram::setMatrix4f( GLint loc, const mat4f& val ) 
    {
        glUniformMatrix4fv( loc, 1, GL_FALSE, val.data );
    }

} // namespace chestnut
