#include "audio_manager.hpp"

#include <SDL_mixer.h>

#include <algorithm> // clamp

namespace chestnut::engine
{
    CAudioManager::CAudioManager() 
    {
        m_globalVolume = 1.f;
        m_musicVolume = 1.f;
    }

    void CAudioManager::addAudio( std::shared_ptr< CAudioResource > audioResource, const char *alias ) 
    {
        if( audioResource )
        {
            m_mapAudioAliasToResource[ alias ] = audioResource;
        }
    }

    std::shared_ptr< CAudioResource > CAudioManager::getAudio( const char *alias ) const
    {
        auto it = m_mapAudioAliasToResource.find( alias );
        if( it != m_mapAudioAliasToResource.end() )
        {
            return it->second;
        }
        
        return std::shared_ptr< CAudioResource >();
    }

    void CAudioManager::removeAudio( const char *alias ) 
    {
        m_mapAudioAliasToResource.erase( alias );
    }


    void CAudioManager::allocateChannels( int channelQuantity ) 
    {
        Mix_AllocateChannels( channelQuantity );
    }

    float CAudioManager::getChannelVolume( audiochannel_t channel ) const
    {
        auto it = m_mapChannelToSFXVolume.find( channel );
        if( it != m_mapChannelToSFXVolume.end() )
        {
            return it->second;
        }

        return 1.f;
    }

    void CAudioManager::setGlobalVolume( float volume ) 
    {
        m_globalVolume = std::clamp( volume, 0.f, 1.f );

        for( auto& [ channel, volume ] : m_mapChannelToSFXVolume )
        {
            // invoking with the same data, because inside it'll account for the new global volume
            setSFXVolume( channel, volume );
        }

        setMusicVolume( m_musicVolume );
    }

    inline int getMixerVolumeFromNormalized( float volume )
    {
        return (int)( (float)MIX_MAX_VOLUME * volume );
    }

    audiochannel_t CAudioManager::playSFX( const char *sfxAlias, audiochannel_t channel, int loops ) 
    {
        audiochannel_t actualChannel = -1;

        auto it = m_mapAudioAliasToResource.find( sfxAlias );
        if( it != m_mapAudioAliasToResource.end() )
        {
            if( it->second->m_type == EAudioResourceType::SFX )
            {
                actualChannel = Mix_PlayChannel( channel, it->second->m_uData.sfx, loops );
            }
        }

        return actualChannel;
    }

    audiochannel_t CAudioManager::playSFXFor( const char *sfxAlias, float seconds, audiochannel_t channel, int loops ) 
    {
        audiochannel_t actualChannel = -1;

        auto it = m_mapAudioAliasToResource.find( sfxAlias );
        if( it != m_mapAudioAliasToResource.end() )
        {
            if( it->second->m_type == EAudioResourceType::SFX )
            {
                actualChannel = Mix_PlayChannelTimed( channel, it->second->m_uData.sfx, loops, (int)( seconds * 1000.f ) );
            }
        }

        return actualChannel;
    }

    void CAudioManager::setSFXVolume( audiochannel_t channel, float volume ) 
    {
        volume = std::clamp( volume, 0.f, 1.f );
        m_mapChannelToSFXVolume[ channel ] = volume;
        volume *= m_globalVolume;
        Mix_Volume( channel, getMixerVolumeFromNormalized( volume ) );
    }

    void CAudioManager::pauseSFX( audiochannel_t channel ) 
    {
        Mix_Pause( channel );
    }

    void CAudioManager::resumeSFX( audiochannel_t channel ) 
    {
        Mix_Resume( channel );
    }

    void CAudioManager::stopSFX( audiochannel_t channel ) 
    {
        Mix_HaltChannel( channel );
    }

    void CAudioManager::playMusic( const char *musicAlias, int loops ) 
    {
        auto it = m_mapAudioAliasToResource.find( musicAlias );
        if( it != m_mapAudioAliasToResource.end() )
        {
            if( it->second->m_type == EAudioResourceType::MUSIC )
            {
                Mix_PlayMusic( it->second->m_uData.music, loops );
            }
        }
    }

    void CAudioManager::playMusicFadeIn( const char *musicAlias, float fadeInSeconds, int loops ) 
    {
        auto it = m_mapAudioAliasToResource.find( musicAlias );
        if( it != m_mapAudioAliasToResource.end() )
        {
            if( it->second->m_type == EAudioResourceType::MUSIC )
            {
                Mix_FadeInMusic( it->second->m_uData.music, loops, (int)( fadeInSeconds * 1000.f ) );
            }
        }
    }

    void CAudioManager::fadeOutMusic( float fadeOutSeconds ) 
    {
        Mix_FadeOutMusic( (int)( fadeOutSeconds * 1000.f ) );
    }

    void CAudioManager::setMusicVolume( float volume ) 
    {
        volume = std::clamp( volume, 0.f, 1.f );
        m_musicVolume = volume;
        volume *= m_globalVolume;
        Mix_VolumeMusic( getMixerVolumeFromNormalized( volume ) );
    }

    void CAudioManager::pauseMusic() 
    {
        Mix_PauseMusic();
    }

    void CAudioManager::resumeMusic() 
    {
        Mix_ResumeMusic();
    }

    void CAudioManager::stopMusic() 
    {
        Mix_HaltMusic();
    }
   
} // namespace chestnut::engine
