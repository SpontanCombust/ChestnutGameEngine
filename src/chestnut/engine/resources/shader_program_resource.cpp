#include "shader_program_resource.hpp"

#include "../debug/log.hpp"

#include <fstream>
#include <sstream>

namespace chestnut::engine
{    
    bool checkShaderCompiled( GLuint shader, std::string& msgBuff ) noexcept
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

    bool checkProgramLinked( GLuint program, std::string& msgBuff ) noexcept
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

    tl::expected<GLuint, const char *> loadShaderFromFile( const char *path, GLenum shaderType ) noexcept
    {
        std::ifstream f = std::ifstream( path, std::ios::in );
        if( f.good() )
        {
            std::stringstream shaderBuffer;
            std::string shaderSource;

            shaderBuffer << f.rdbuf();
            shaderSource = shaderBuffer.str();

            const char *shaderSourceRawStr = shaderSource.c_str();

            f.close();


            GLuint shader = glCreateShader( shaderType );
            glShaderSource( shader, 1, &shaderSourceRawStr, NULL );
            glCompileShader( shader );

            std::string errMsg;
            if( !checkShaderCompiled( shader, errMsg ) )
            {
                LOG_ERROR( "Failed to compile the shader from file: " << path );
                LOG_ERROR( "Error: " << errMsg );
                glDeleteShader( shader );
                return tl::make_unexpected<const char *>("Shader compilation error");
            }
            else
            {
                return shader;
            }
        }
        else
        {
            LOG_ERROR( "Failed to open shader source file: " << path );
            return tl::make_unexpected<const char *>("Shader file open error");
        }
    }

    tl::expected<GLuint, const char *> createAndLinkShaderProgram(GLuint vertexShader, GLuint fragmentShader) noexcept
    {
        GLuint program = glCreateProgram();
        glAttachShader( program, vertexShader );
        glAttachShader( program, fragmentShader );
        glLinkProgram( program );

        glDetachShader( program, fragmentShader );
        glDetachShader( program, vertexShader );
        glDeleteShader( fragmentShader );
        glDeleteShader( vertexShader );

        std::string errMsg;
        if( !checkProgramLinked( program, errMsg ) )
        {
            LOG_ERROR( "Failed to link the shader program" );
            LOG_ERROR( "Error: " << errMsg );
            glDeleteProgram( program );
            return tl::make_unexpected<const char *>("Shader program linking error");
        }
        else
        {
            return program;
        }
    }

    tl::expected<GLuint, const char *> loadOpenGLShaderProgramFromFiles( const char *vertPath, const char *fragPath ) noexcept
    {
        GLuint vertShader;
        GLuint fragShader;
        
        if( auto shader = loadShaderFromFile( vertPath, GL_VERTEX_SHADER ) ) {
            vertShader = *shader;
        } else {
            return tl::unexpected(shader.error());
        }
        
        if( auto shader = loadShaderFromFile( fragPath, GL_FRAGMENT_SHADER ) ) {
            fragShader = *shader;
        } else {
            return tl::unexpected(shader.error());
        }

        return createAndLinkShaderProgram( vertShader, fragShader );
    }

    




    CShaderProgramResource::CShaderProgramResource() noexcept
    {
        m_programID = 0;
        m_vertexShaderPath = "";
        m_fragmentShaderPath = "";
    }

    CShaderProgramResource::~CShaderProgramResource() noexcept
    {
        glDeleteProgram( m_programID );
    }

    GLint CShaderProgramResource::getAttributeLocation( const char *attrName ) noexcept
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

    GLint CShaderProgramResource::getUniformLocation( const char *uniformName ) noexcept
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




    tl::expected<std::shared_ptr<CShaderProgramResource>, const char *> CShaderProgramResource::loadFromFiles( const char *vertPath, const char *fragPath ) noexcept
    {
        LOG_INFO("Loading shader program from files: " << vertPath << " and " << fragPath << "..." );

        auto program = loadOpenGLShaderProgramFromFiles( vertPath, fragPath );

        if( program ) 
        {
            CShaderProgramResource *resource = new CShaderProgramResource();
            resource->m_programID = *program;
            resource->m_vertexShaderPath = vertPath;
            resource->m_fragmentShaderPath = fragPath;

            return std::shared_ptr<CShaderProgramResource>( resource );
        } 
        
        return tl::unexpected(program.error());
    }

} // namespace chestnut::engine
