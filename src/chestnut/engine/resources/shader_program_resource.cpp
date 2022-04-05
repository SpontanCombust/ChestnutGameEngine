#include "shader_program_resource.hpp"

#include "../debug/log.hpp"
#include "../misc/exception.hpp"

#include <fstream>
#include <sstream>

namespace chestnut::engine
{    
    bool checkShaderCompiled( GLuint shader, std::string& msgBuff )
    {
        GLint compiled;

        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if( compiled == GL_TRUE )
        {
            return true;
        }
        else
        {
            GLint logMaxLength;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logMaxLength );

            GLsizei logLength;
            GLchar *logBuffer = new char[logMaxLength];
            glGetShaderInfoLog( shader, logMaxLength, &logLength, logBuffer );

            if( logLength > 0 )
            {
                msgBuff = std::string( logBuffer );
            }

            delete[] logBuffer;

            return false;
        }
    }

    bool checkProgramLinked( GLuint program, std::string& msgBuff )
    {
        GLint linked;

        glGetProgramiv( program, GL_LINK_STATUS, &linked );
        if( linked == GL_TRUE )
        {
            return true;
        }
        else
        {
            GLint logMaxLength;
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logMaxLength );

            GLsizei logLength;
            GLchar *logBuffer = new char[logMaxLength];
            glGetProgramInfoLog( program, logMaxLength, &logLength, logBuffer );

            if( logLength > 0 )
            {
                msgBuff = std::string( logBuffer );
            }

            delete[] logBuffer;

            return false;
        }
    }

    GLuint loadShaderFromFile( const char *path, GLenum shaderType )
    {
        GLuint shader;

        std::ifstream f = std::ifstream( path, std::ios::in );
        if( f.good() )
        {
            std::stringstream shaderBuffer;
            std::string shaderSource;

            shaderBuffer << f.rdbuf();
            shaderSource = shaderBuffer.str();

            const char *shaderSourceRawStr = shaderSource.c_str();

            f.close();


            shader = glCreateShader( shaderType );
            glShaderSource( shader, 1, &shaderSourceRawStr, NULL );
            glCompileShader( shader );

            std::string errMsg;
            if( !checkShaderCompiled( shader, errMsg ) )
            {
                LOG_ERROR( "Failed to compile the shader from file: " << path );
                LOG_ERROR( "Error: " << errMsg );
                glDeleteShader( shader );
                shader = 0;
            }
        }
        else
        {
            LOG_ERROR( "Failed to open shader source file: " << path );
            shader = 0;
        }

        return shader;
    }

    GLuint loadOpenGLShaderProgramFromFiles( const char *vertPath, const char *fragPath )
    {
        GLuint program;
        GLuint vertShader;
        GLuint fragShader;

        program = glCreateProgram();

        vertShader = loadShaderFromFile( vertPath, GL_VERTEX_SHADER );
        if( vertShader == 0 )
        {
            glDeleteProgram( program );
            throw ChestnutResourceLoadException( "shader", vertPath, "vertex shader load failure" );
        }
        glAttachShader( program, vertShader );

        fragShader = loadShaderFromFile( fragPath, GL_FRAGMENT_SHADER );
        if( fragShader == 0 )
        {
            glDeleteShader( vertShader );
            glDeleteProgram( program );
            throw ChestnutResourceLoadException( "shader", fragPath, "fragment shader load failure" );
        }
        glAttachShader( program, fragShader );

        glLinkProgram( program );
        std::string errMsg;
        if( !checkProgramLinked( program, errMsg ) )
        {
            LOG_ERROR( "Failed to link the program for vertex shader " << vertPath << " and fragment shader " << fragPath );
            LOG_ERROR( "Error: " << errMsg );
            glDeleteShader( fragShader );
            glDeleteShader( vertShader );
            glDeleteProgram( program );
            throw ChestnutResourceLoadException( "CShaderProgramResource", vertPath + std::string(" and ") + fragPath, "shader program linkage failure" );
        }

        glDeleteShader( fragShader );
        glDeleteShader( vertShader );

        return program;
    }

    




    CShaderProgramResource::CShaderProgramResource() 
    {
        m_programID = 0;
        m_vertexShaderPath = "";
        m_fragmentShaderPath = "";
    }

    CShaderProgramResource::~CShaderProgramResource() 
    {
        glDeleteProgram( m_programID );
    }

    GLint CShaderProgramResource::getAttributeLocation( const char *attrName ) 
    {
        GLint loc;

        if( m_mapAttributeNameToLocation.find( attrName ) != m_mapAttributeNameToLocation.end() )
        {
            loc = m_mapAttributeNameToLocation[ attrName ];
        }
        else
        {
            loc = glGetAttribLocation( m_programID, attrName );

            if( loc == -1 )
            {
                LOG_WARNING( "Couldn't find attribute with name " << attrName << " in program " << m_programID );
            }
            else
            {
                m_mapAttributeNameToLocation[ attrName ] = loc;   
            }
        }

        return loc;
    }

    GLint CShaderProgramResource::getUniformLocation( const char *uniformName ) 
    {
        GLint loc;

        if( m_mapUniformNameToLocation.find( uniformName ) != m_mapUniformNameToLocation.end() )
        {
            loc = m_mapUniformNameToLocation[ uniformName ];
        }
        else
        {
            loc = glGetUniformLocation( m_programID, uniformName );

            if( loc == -1 )
            {
                LOG_WARNING( "Couldn't find uniform with name " << uniformName << " in program " << m_programID );
            }
            else
            {
                m_mapUniformNameToLocation[ uniformName ] = loc;   
            }
        }
        
        return loc;
    }




    std::shared_ptr<CShaderProgramResource> CShaderProgramResource::loadFromFiles( const char *vertPath, const char *fragPath )
    {
        // let the possible exception propagate
        GLuint program = loadOpenGLShaderProgramFromFiles( vertPath, fragPath );

        CShaderProgramResource *resource = new CShaderProgramResource();
        resource->m_programID = program;
        resource->m_vertexShaderPath = vertPath;
        resource->m_fragmentShaderPath = fragPath;

        return std::shared_ptr<CShaderProgramResource>( resource );
    }

} // namespace chestnut::engine
