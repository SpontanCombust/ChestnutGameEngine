#include "resource_manager.hpp"

#include "engine/libs.hpp"
#include "engine/debug/debug.hpp"

#include <fstream>
#include <sstream>

namespace chestnut
{
    // ================== PURE FUNCTIONS ==================

    bool checkShaderCompiled( unsigned int shader, std::string& msgBuff )
    {
        int compiled;

        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if( compiled == GL_TRUE )
        {
            return true;
        }
        else
        {
            int logMaxLength;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logMaxLength );

            int logLength;
            char *logBuffer = new char[logMaxLength];
            glGetShaderInfoLog( shader, logMaxLength, &logLength, logBuffer );

            if( logLength > 0 )
            {
                msgBuff = std::string( logBuffer );
            }

            delete[] logBuffer;

            return false;
        }
    }

    bool checkProgramLinked( unsigned int program, std::string& msgBuff )
    {
        int linked;

        glGetProgramiv( program, GL_LINK_STATUS, &linked );
        if( linked == GL_TRUE )
        {
            return true;
        }
        else
        {
            int logMaxLength;
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logMaxLength );

            int logLength;
            char *logBuffer = new char[logMaxLength];
            glGetProgramInfoLog( program, logMaxLength, &logLength, logBuffer );

            if( logLength > 0 )
            {
                msgBuff = std::string( logBuffer );
            }

            delete[] logBuffer;

            return false;
        }
    }

    unsigned int loadShaderFromFile( const std::string& path, unsigned int shaderType )
    {
        unsigned int shader;

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
                LOG_CHANNEL( "RESOURCE_MANAGER", "Failed to compile the shader from file: " << path );
                LOG_CHANNEL( "RESOURCE_MANAGER", "Error: " << errMsg );
                glDeleteShader( shader );
                shader = 0;
            }
        }
        else
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", "Failed to open shader source file: " << path );
            shader = 0;
        }

        return shader;
    }

    CShaderProgram loadShaderProgramFromFiles( const std::string& vertPath, const std::string& fragPath )
    {
        unsigned int program;
        unsigned int vertShader;
        unsigned int fragShader;

        program = glCreateProgram();

        vertShader = loadShaderFromFile( vertPath, GL_VERTEX_SHADER );
        if( vertShader == 0 )
        {
            glDeleteProgram( program );
            return CShaderProgram( 0 );
        }
        glAttachShader( program, vertShader );

        fragShader = loadShaderFromFile( fragPath, GL_FRAGMENT_SHADER );
        if( fragShader == 0 )
        {
            glDeleteShader( vertShader );
            glDeleteProgram( program );
            return CShaderProgram( 0 );
        }
        glAttachShader( program, fragShader );

        glLinkProgram( program );
        std::string errMsg;
        if( !checkProgramLinked( program, errMsg ) )
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", "Failed to link the program for vertex shader " << vertPath << " and fragment shader " << fragPath );
            LOG_CHANNEL( "RESOURCE_MANAGER", "Error: " << errMsg );
            glDeleteShader( fragShader );
            glDeleteShader( vertShader );
            glDeleteProgram( program );
            return CShaderProgram( 0 );
        }

        glDeleteShader( fragShader );
        glDeleteShader( vertShader );

        return CShaderProgram( program );
    }

    // ================== CLASS FUNCTIONS ==================

    CResourceManager::~CResourceManager() 
    {
        unsigned int id;

        for( const auto& [ hash, shader ] : m_mapPathHashToShader )
        {
            id = shader.getID();
            glDeleteProgram( id );
        }
    }

    size_t CResourceManager::strHash(const std::string& str) 
    {
        return std::hash< std::string >()( str );
    }

    CShaderProgram CResourceManager::loadShaderProgram( const std::string& vertPath, const std::string& fragPath ) 
    {
        CShaderProgram prog = loadShaderProgramFromFiles( vertPath, fragPath );

        if( prog.getID() != 0 )
        {
            // a hash created from 2 other hashes (by using XOR)
            size_t hash = strHash( vertPath ) ^ strHash( fragPath );        
            m_mapPathHashToShader.insert( std::make_pair( hash, prog ) );
        }

        return prog;
    }

    CTexture2D CResourceManager::loadTexture( const std::string& path ) 
    {
        CTexture2D tex;

        try
        {
            std::shared_ptr<CTexture2DResource> resource = loadTextureResourceFromFile( path );
            tex = CTexture2D( resource );

            size_t hash = strHash( path );
            m_mapPathHashToTextureResource.insert( std::make_pair( hash, resource ) );
        }
        catch( const std::exception& e )
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", e.what() );
        }

        return tex;
    }

} // namespace chestnut
