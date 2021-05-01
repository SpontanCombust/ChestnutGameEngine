#include "shader_program.hpp"

#include "engine/libs.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
    CShaderProgram::CShaderProgram() 
    {
        m_programID = 0;
    }

    CShaderProgram::CShaderProgram( unsigned int programID ) 
    {
        m_programID = programID;
    }

    unsigned int CShaderProgram::getID() const
    {
        return m_programID;
    }

    bool CShaderProgram::isValid() const
    {
        return m_programID != 0;
    }

    void CShaderProgram::bind()
    {
        glUseProgram( m_programID );
    }

    void CShaderProgram::unbind()
    {
        glUseProgram(0);
    }

    int CShaderProgram::getAttributeLocation( std::string attrName ) 
    {
        GLint loc;

        if( m_mapVarLocations.find( attrName ) != m_mapVarLocations.end() )
        {
            loc = m_mapVarLocations[ attrName ];
        }
        else
        {
            loc = glGetAttribLocation( m_programID, attrName.c_str() );

            if( loc == -1 )
            {
                LOG_CHANNEL( "SHADER_PROGRAM", "Couldn't find attribute with name " << attrName << " in program " << m_programID );
            }
            else
            {
                m_mapVarLocations[ attrName ] = loc;   
            }
        }

        return loc;
    }

    int CShaderProgram::getUniformLocation( std::string uniformName ) 
    {
        GLint loc;

        if( m_mapVarLocations.find( uniformName ) != m_mapVarLocations.end() )
        {
            loc = m_mapVarLocations[ uniformName ];
        }
        else
        {
            loc = glGetUniformLocation( m_programID, uniformName.c_str() );

            if( loc == -1 )
            {
                LOG_CHANNEL( "SHADER_PROGRAM", "Couldn't find uniform with name " << uniformName << " in program " << m_programID );
            }
            else
            {
                m_mapVarLocations[ uniformName ] = loc;   
            }
        }
        
        return loc;
    }

    bool CShaderProgram::setInt( const std::string& unifName, int val ) 
    {
        int loc = getUniformLocation( unifName );
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
        int loc = getUniformLocation( unifName );
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
        int loc = getUniformLocation( unifName );
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
        int loc = getUniformLocation( unifName );
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
        int loc = getUniformLocation( unifName );
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
        int loc = getUniformLocation( unifName );
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

    void CShaderProgram::setInt( int loc, int val ) 
    {
        glUniform1i( loc, val );
    }

    void CShaderProgram::setVector2f( int loc, const vec2f& val ) 
    {
        glUniform2fv( loc, 1, val.data );
    }

    void CShaderProgram::setVector3f( int loc, const vec3f& val ) 
    {
        glUniform3fv( loc, 1, val.data );
    }

    void CShaderProgram::setVector4f( int loc, const vec4f& val ) 
    {
        glUniform4fv( loc, 1, val.data );
    }

    void CShaderProgram::setMatrix3f( int loc, const mat3f& val ) 
    {
        glUniformMatrix3fv( loc, 1, GL_FALSE, val.data );
    }

    void CShaderProgram::setMatrix4f( int loc, const mat4f& val ) 
    {
        glUniformMatrix4fv( loc, 1, GL_FALSE, val.data );
    }

} // namespace chestnut
