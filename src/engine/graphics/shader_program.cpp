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

} // namespace chestnut
