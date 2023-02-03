#include "chestnut/engine/audio/audio_manager.hpp"

#include "chestnut/engine/debug/log.hpp"

#include <SDL_mixer.h>

#include <algorithm> // clamp

namespace chestnut::engine
{
    CAudioManager::CAudioManager() 
    {
        m_globalVolume = 1.f;
        m_musicVolume = 1.f;
    }

    bool CAudioManager::addAudio(std::shared_ptr<CMusicResource> music) 
    {
        auto name = music->m_location->stem().string();

        auto it = m_mapNameToMusic.find(name);
        if(it != m_mapNameToMusic.end())
        {
            LOG_ERROR("Music with name " << name << " is already present in the manager! Make sure the file name is unique.");
            return false;
        }

        m_mapNameToMusic[name] = music;

        return true;
    }

    bool CAudioManager::addAudio(std::shared_ptr<CSoundBankResource> soundBank) 
    {
        auto bnkName = soundBank->m_location->stem().string();

        if(m_mapNameToSoundBank.find(bnkName) != m_mapNameToSoundBank.end())
        {
            LOG_ERROR("Soundbank with name " << bnkName << " is already present in the manager! Make sure the file name is unique.");
            return false;
        }

        m_mapNameToSoundBank[bnkName] = soundBank;

        for(auto [sfxName, sfx] : soundBank->m_mapNameToSFXHandle)
        {
            if(m_mapNameToSFXHandle.find(sfxName) != m_mapNameToSFXHandle.end())
            {
                LOG_WARNING("Tried to add from sound bank " << bnkName << " sound with name " << sfxName << 
                            " which is already present in the manager! Make sure the sound alias is unique.");
            }
            else
            {
                m_mapNameToSFXHandle[sfxName] = sfx;
            }
        }

        return true;
    }

    bool CAudioManager::hasMusic(const char *musicName) const
    {
        return m_mapNameToMusic.find(musicName) != m_mapNameToMusic.end();
    }

    bool CAudioManager::hasSoundBank(const char *soundBankName) const
    {
        return m_mapNameToSoundBank.find(soundBankName) != m_mapNameToSoundBank.end();
    }

    bool CAudioManager::hasSFX(const char *sfxName) const
    {
        return m_mapNameToSFXHandle.find(sfxName) != m_mapNameToSFXHandle.end();
    }

    bool CAudioManager::removeMusic(const char *musicName) 
    {
        auto it = m_mapNameToMusic.find(musicName);
        if(it != m_mapNameToMusic.end())
        {
            m_mapNameToMusic.erase(it);
            return true;
        }

        return false;
    }

    bool CAudioManager::removeSoundBank(const char *soundBankName) 
    {
        auto it = m_mapNameToSoundBank.find(soundBankName);
        if(it != m_mapNameToSoundBank.end())
        {
            for(auto [sfxName, _] : it->second->m_mapNameToSFXHandle)
            {
                m_mapNameToSFXHandle.erase(sfxName);
            }

            m_mapNameToSoundBank.erase(it);
            return true;
        }

        return false;
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

        for( auto& [ ch, v ] : m_mapChannelToSFXVolume )
        {
            // invoking with the same data, because inside it'll account for the new global volume
            setSFXVolume( ch, v );
        }

        setMusicVolume( m_musicVolume );
    }

    inline int getMixerVolumeFromNormalized( float volume )
    {
        return (int)( (float)MIX_MAX_VOLUME * volume );
    }

    audiochannel_t CAudioManager::playSFX(const char *sfxName, int times, audiochannel_t channel) 
    {
        if(times == 0)
        {
            return -1;
        }

        audiochannel_t actualChannel = -1;
        int loops = (times > 0) ? times - 1 : -1;

        auto it = m_mapNameToSFXHandle.find( sfxName );
        if( it != m_mapNameToSFXHandle.end() )
        {
            actualChannel = Mix_PlayChannel(channel, it->second, loops);
        }

        return actualChannel;
    }

    audiochannel_t CAudioManager::playSFXFor( const char *sfxName, float seconds, int times, audiochannel_t channel) 
    {
        if(times == 0)
        {
            return -1;
        }

        audiochannel_t actualChannel = -1;
        int loops = (times > 1) ? times - 1 : -1;

        auto it = m_mapNameToSFXHandle.find( sfxName );
        if( it != m_mapNameToSFXHandle.end() )
        {
            actualChannel = Mix_PlayChannelTimed( channel, it->second, loops, (int)( seconds * 1000.f ) );
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

    void CAudioManager::playMusic( const char *musicName, int times ) 
    {
        if(times == 0)
        {
            return;
        }

        int loops = (times > 0) ? times - 1 : -1;

        auto it = m_mapNameToMusic.find( musicName );
        if( it != m_mapNameToMusic.end() )
        {
            Mix_PlayMusic( it->second->m_musicHandle, loops );
        }
    }

    void CAudioManager::playMusicFadeIn( const char *musicName, float fadeInSeconds, int times ) 
    {
        if(times == 0)
        {
            return;
        }

        int loops = (times > 0) ? times - 1 : -1;
        
        auto it = m_mapNameToMusic.find( musicName );
        if( it != m_mapNameToMusic.end() )
        {
            Mix_FadeInMusic( it->second->m_musicHandle, loops, (int)( fadeInSeconds * 1000.f ) );
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
