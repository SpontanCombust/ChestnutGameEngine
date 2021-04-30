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



    CTexture2D loadTextureFromFile( const std::string& path )
    {
        SDL_Surface *surf = IMG_Load( path.c_str() );

        if( !surf )
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", "Couldn't load file at " << path );
            return CTexture2D();
        }

        if( surf->w != surf->h || ( surf->w & ( surf->w - 1 ) ) != 0 )
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", "Warning! Loading non-power-of-two texture from " << path );
        }

        int width = surf->w;
        int height = surf->h;
        void *pixels = surf->pixels;

        int bytesPerPixel = (int)surf->format->BytesPerPixel;
        bool firstRed = ( surf->format->Rmask == 0x000000ff );
        unsigned int pixelFormat;

        if( bytesPerPixel == 4 )
        {
            if( firstRed )
            {
                pixelFormat = GL_RGBA;
            }
            else
            {
                pixelFormat = GL_BGRA;
            }
        }
        else if( bytesPerPixel == 3 )
        {
            if( firstRed )
            {
                pixelFormat = GL_RGB;
            }
            else
            {
                pixelFormat = GL_BGR;
            }
        }
        else if( bytesPerPixel == 2 )
        {
            pixelFormat = GL_RG;
        }
        else
        {
            pixelFormat = GL_RED;
        }
        
        CTexture2D tex = loadTextureFromPixels( pixels, width, height, pixelFormat );
        
        SDL_FreeSurface( surf );

        return tex;
    }

    CTexture2D loadTextureFromPixels( void *pixels, int width, int height, unsigned int pixelFormat )
    {
        unsigned int texID;

        glGenTextures( 1, &texID );

        glBindTexture( GL_TEXTURE_2D, texID );
        
        glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, pixels );

        unsigned int err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", "Error occured while loading texture from pixels! Error:" );
            LOG_CHANNEL( "RESOURCE_MANAGER", (char *)gluErrorString( err ) );
            glDeleteTextures( 1, &texID );
            texID = 0;
        }

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

        glBindTexture( GL_TEXTURE_2D, 0 );

        return CTexture2D( texID, width, height, pixelFormat );
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

        for( const auto& [ hash, texture ] : m_mapPathHashToTexture )
        {
            id = texture.getID();
            glDeleteTextures( 1, &id );
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
        CTexture2D tex = loadTextureFromFile( path );

        if( tex.getID() != 0 )
        {
            size_t hash = strHash( path );
            m_mapPathHashToTexture.insert( std::make_pair( hash, tex ) );
        }

        return tex;
    }

} // namespace chestnut
