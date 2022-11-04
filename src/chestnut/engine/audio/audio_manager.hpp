#pragma once

#include "chestnut/engine/macros.hpp"
#include "../resources/audio_resource.hpp"
#include "../types.hpp"

#include <string>
#include <unordered_map>

namespace chestnut::engine
{
    //TODO fade in, fade out
    class CHESTNUT_API CAudioManager
    {
    private:
        std::unordered_map< std::string, std::shared_ptr< CAudioResource > > m_mapAudioAliasToResource;

        float m_globalVolume;
        std::unordered_map< audiochannel_t, float > m_mapChannelToSFXVolume;
        float m_musicVolume;


    public:
        CAudioManager();
        

        void addAudio( std::shared_ptr< CAudioResource > audioResource, const char *alias );
        std::shared_ptr< CAudioResource > getAudio( const char *alias ) const; // will return empty shared pointer if there's no such audio
        void removeAudio( const char *alias );


        void allocateChannels( int channelQuantity );

        // Volume should be between 0 (total silence) and 1 (max volume). Otherwise it'll get clamped to it.
        void setGlobalVolume( float volume );


        // channel = -1 for first available channel
        // loops = -1 for infinite loops
        // Returns the channel SFX is played on or -1 on error
        audiochannel_t playSFX( const char *sfxAlias, audiochannel_t channel = -1, int loops = 0 );
        // channel = -1 for first available channel
        // loops = -1 for infinite loops
        // Returns the channel SFX is played on or -1 on error
        audiochannel_t playSFXFor( const char *sfxAlias, float seconds, audiochannel_t channel = -1, int loops = 0 );

        // Volume should be between 0 (total silence) and 1 (max volume). Otherwise it'll get clamped to it.
        // channel = -1 to set it for all channels
        void setSFXVolume( audiochannel_t channel, float volume );

        // channel = -1 to pause all channels
        void pauseSFX( audiochannel_t channel );

        // channel = -1 to resume all channels
        void resumeSFX( audiochannel_t channel );

        // channel = -1 to stop on all channels
        void stopSFX( audiochannel_t channel );


        // loops = -1 for infinite loops
        void playMusic( const char *musicAlias, int loops = 0 );

        // loops = -1 for infinite loops
        void playMusicFadeIn( const char *musicAlias, float fadeInSeconds, int loops = 0 );

        void fadeOutMusic( float fadeOutSeconds );

        // Volume should be between 0 (total silence) and 1 (max volume). Otherwise it'll get clamped to it.
        void setMusicVolume( float volume );

        void pauseMusic();

        void resumeMusic();

        void stopMusic();


    private:
        float getChannelVolume( audiochannel_t channel ) const;
    };
    
} // namespace chestnut::engine
