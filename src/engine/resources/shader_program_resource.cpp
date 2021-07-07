#include "shader_program_resource.hpp"

#include "engine/debug/debug.hpp"
#include "engine/misc/exception.hpp"

#include <fstream>
#include <sstream>

namespace chestnut
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

    GLuint loadShaderFromFile( const std::string& path, GLenum shaderType )
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
                LOG_CHANNEL( "SHADER_PROGRAM_RESOURCE", "Failed to compile the shader from file: " << path );
                LOG_CHANNEL( "SHADER_PROGRAM_RESOURCE", "Error: " << errMsg );
                glDeleteShader( shader );
                shader = 0;
            }
        }
        else
        {
            LOG_CHANNEL( "SHADER_PROGRAM_RESOURCE", "Failed to open shader source file: " << path );
            shader = 0;
        }

        return shader;
    }

    // Throws exception if fails to load the shader program
    GLuint loadOpenGLShaderProgramFromFiles( const std::string& vertPath, const std::string& fragPath )
    {
        GLuint program;
        GLuint vertShader;
        GLuint fragShader;

        program = glCreateProgram();

        vertShader = loadShaderFromFile( vertPath, GL_VERTEX_SHADER );
        if( vertShader == 0 )
        {
            glDeleteProgram( program );
            throw ChestnutException( "Failed to load vertex shader!" );
        }
        glAttachShader( program, vertShader );

        fragShader = loadShaderFromFile( fragPath, GL_FRAGMENT_SHADER );
        if( fragShader == 0 )
        {
            glDeleteShader( vertShader );
            glDeleteProgram( program );
            throw ChestnutException( "Failed to load fragment shader!" );
        }
        glAttachShader( program, fragShader );

        glLinkProgram( program );
        std::string errMsg;
        if( !checkProgramLinked( program, errMsg ) )
        {
            LOG_CHANNEL( "SHADER_PROGRAM_RESOURCE", "Failed to link the program for vertex shader " << vertPath << " and fragment shader " << fragPath );
            LOG_CHANNEL( "SHADER_PROGRAM_RESOURCE", "Error: " << errMsg );
            glDeleteShader( fragShader );
            glDeleteShader( vertShader );
            glDeleteProgram( program );
            throw ChestnutException( "Failed to link shader program!" );
        }

        glDeleteShader( fragShader );
        glDeleteShader( vertShader );

        return program;
    }

    




    CShaderProgramResource::CShaderProgramResource() 
    {
        this->programID = 0;
    }

    CShaderProgramResource::CShaderProgramResource( GLuint programID ) 
    {
        this->programID = programID;
    }

    bool CShaderProgramResource::isValid() const
    {
        if( programID != 0 )
        {
            return true;
        }
        return false;
    }

    CShaderProgramResource::~CShaderProgramResource() 
    {
        if( isValid() )
        {
            glDeleteProgram( programID );
        }
    }

    GLint CShaderProgramResource::getAttributeLocation( std::string attrName ) 
    {
        GLint loc;

        if( mapAttributeNameToLocation.find( attrName ) != mapAttributeNameToLocation.end() )
        {
            loc = mapAttributeNameToLocation[ attrName ];
        }
        else
        {
            loc = glGetAttribLocation( programID, attrName.c_str() );

            if( loc == -1 )
            {
                LOG_CHANNEL( "SHADER_PROGRAM_RESOURCE", "Couldn't find attribute with name " << attrName << " in program " << programID );
            }
            else
            {
                mapAttributeNameToLocation[ attrName ] = loc;   
            }
        }

        return loc;
    }

    GLint CShaderProgramResource::getUniformLocation( std::string uniformName ) 
    {
        GLint loc;

        if( mapUniformNameToLocation.find( uniformName ) != mapUniformNameToLocation.end() )
        {
            loc = mapUniformNameToLocation[ uniformName ];
        }
        else
        {
            loc = glGetUniformLocation( programID, uniformName.c_str() );

            if( loc == -1 )
            {
                LOG_CHANNEL( "SHADER_PROGRAM_RESOURCE", "Couldn't find uniform with name " << uniformName << " in program " << programID );
            }
            else
            {
                mapUniformNameToLocation[ uniformName ] = loc;   
            }
        }
        
        return loc;
    }




    std::shared_ptr<CShaderProgramResource> loadShaderProgramResourceFromFiles( const std::string& vertPath, const std::string& fragPath )
    {
        // let the eventual exception propagate
        GLuint program = loadOpenGLShaderProgramFromFiles( vertPath, fragPath );

        return std::make_shared<CShaderProgramResource>( program );
    }

} // namespace chestnut
