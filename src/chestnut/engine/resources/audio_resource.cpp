#include "chestnut/engine/resources/audio_resource.hpp"

#include "chestnut/engine/debug/log.hpp"

#include <SDL_mixer.h>

namespace chestnut::engine
{
    tl::expected<Mix_Chunk*, const char *> loadMixerChunkFromFile( const char *sfxPath ) noexcept
    {
        Mix_Chunk *sample = Mix_LoadWAV( sfxPath );
        if( !sample )
        {
            LOG_ERROR( "Failed to load sound effect from file " << sfxPath );
            LOG_ERROR( "SDL_mixer Error: " << Mix_GetError() );
            return tl::unexpected(Mix_GetError());
        }

        return sample;
    }

    tl::expected<Mix_Music*, const char *> loadMixerMusicFromFile( const char *musicPath ) noexcept
    {
        Mix_Music *music = Mix_LoadMUS( musicPath );
        if( !music )
        {
            LOG_ERROR( "Failed to load music from file " << musicPath );
            LOG_ERROR( "SDL_mixer Error: " << Mix_GetError() );
            return tl::unexpected(Mix_GetError());
        }

        return music;
    }


    chestnut::engine::CAudioResource::CAudioResource() noexcept
    {
        m_audioPath = "";
        m_type = EAudioResourceType::SFX;
        m_uData.sfx = nullptr;
    }

    chestnut::engine::CAudioResource::~CAudioResource() noexcept
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

    tl::expected<std::shared_ptr<CAudioResource>, const char *> CAudioResource::loadFromFile(const char *audioPath, EAudioResourceType type) noexcept
    {
        CAudioResource::UAudio audio;

        LOG_INFO("Loading audio resource from file " << audioPath << "...");

        if( type == EAudioResourceType::SFX )
        {
            auto sfx = loadMixerChunkFromFile( audioPath );
            if(sfx.has_value())
            {
                audio.sfx = sfx.value();
            }
            else
            {
                return tl::unexpected(sfx.error());
            }
        }
        else
        {
            auto music = loadMixerMusicFromFile( audioPath );
            if(music.has_value())
            {
                audio.music = music.value();
            }
            else
            {
                return tl::unexpected(music.error());
            }
        }

        CAudioResource *resource = new CAudioResource();
        resource->m_audioPath = audioPath;
        resource->m_type = type;
        resource->m_uData = audio;
        
        return std::shared_ptr< CAudioResource >( resource );
    }

} // namespace chestnut::engine
