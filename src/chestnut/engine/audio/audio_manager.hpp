#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/music_resource.hpp"
#include "chestnut/engine/resources/sound_bank_resource.hpp"
#include "chestnut/engine/types.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace chestnut::engine
{
    class CHESTNUT_API CAudioManager
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<CMusicResource>> m_mapNameToMusic;

        std::unordered_map<std::string, std::shared_ptr<CSoundBankResource>> m_mapNameToSoundBank;
        std::unordered_map<std::string, Mix_Chunk *> m_mapNameToSFXHandle;

        float m_globalVolume;
        std::unordered_map< audiochannel_t, float > m_mapChannelToSFXVolume;
        float m_musicVolume;


    public:
        CAudioManager();
        

        bool addAudio(std::shared_ptr<CMusicResource> music);
        bool addAudio(std::shared_ptr<CSoundBankResource> soundBank);

        bool hasMusic(const char *musicName) const;
        bool hasSoundBank(const char *soundBankName) const;
        bool hasSFX(const char *sfxName) const;

        bool removeMusic(const char *musicName);
        bool removeSoundBank(const char *soundBankName);


        void allocateChannels( int channelQuantity );

        // Volume should be between 0 (total silence) and 1 (max volume). Otherwise it'll get clamped to it.
        void setGlobalVolume( float volume );


        // times = -1 for infinite amount of times
        // channel = -1 for first available channel
        // Returns the channel SFX is played on or -1 on error
        audiochannel_t playSFX(const char *sfxName, int times = 1, audiochannel_t channel = -1);
        // times = -1 for infinite amount of times
        // channel = -1 for first available channel
        // Returns the channel SFX is played on or -1 on error
        audiochannel_t playSFXFor(const char *sfxName, float seconds, int times = 1, audiochannel_t channel = -1);

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
        void playMusic( const char *musicName, int times = 1 );
        // loops = -1 for infinite loops
        void playMusicFadeIn( const char *musicName, float fadeInSeconds, int times = 1 );
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
