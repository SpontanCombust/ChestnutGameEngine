#include "audio_resource.hpp"

#include "../debug/log.hpp"
#include "../misc/exception.hpp"

#include <SDL2/SDL_mixer.h>

namespace chestnut::engine
{
    Mix_Chunk* loadMixerChunkFromFile( const std::string& sfxPath )
    {
        Mix_Chunk *sample = Mix_LoadWAV( sfxPath.c_str() );
        if( !sample )
        {
            LOG_ERROR( "Failed to load sound effect from file " << sfxPath );
            throw ChestnutResourceLoadException( "CAudioResource", sfxPath, Mix_GetError() );
        }

        return sample;
    }

    Mix_Music* loadMixerMusicFromFile( const std::string& musicPath )
    {
        Mix_Music *music = Mix_LoadMUS( musicPath.c_str() );
        if( !music )
        {
            LOG_ERROR( "Failed to load music from file " << musicPath );
            throw ChestnutResourceLoadException( "CAudioResource", musicPath, Mix_GetError() );
        }

        return music;
    }


    chestnut::engine::CAudioResource::CAudioResource() 
    {
        m_audioPath = "";
        m_type = EAudioResourceType::SFX;
        m_uData.sfx = nullptr;
    }

    chestnut::engine::CAudioResource::~CAudioResource() 
    {
        if( m_type == EAudioResourceType::SFX )
        {
            Mix_FreeChunk( m_uData.sfx );
        }
        else
        {
            Mix_FreeMusic( m_uData.music );
        }
    }


    std::shared_ptr< CAudioResource > loadAudioResourceFromFile( const std::string& audioPath, EAudioResourceType type )
    {
        CAudioResource::UAudio audio;

        if( type == EAudioResourceType::SFX )
        {
            // let the exception propagate if happens
            audio.sfx = loadMixerChunkFromFile( audioPath );
        }
        else
        {
            // let the exception propagate if happens
            audio.music = loadMixerMusicFromFile( audioPath );
        }

        CAudioResource *resource = new CAudioResource();
        resource->m_audioPath = audioPath;
        resource->m_type = type;
        resource->m_uData = audio;
        
        return std::shared_ptr< CAudioResource >( resource );
    }

} // namespace chestnut::engine
