#ifndef __CHESTNUT_ENGINE_AUDIO_RESOURCE_H__
#define __CHESTNUT_ENGINE_AUDIO_RESOURCE_H__

#include "resource.hpp"

#include <SDL2/SDL_mixer.h> //FIXME It'd better if this wasn't here, but whatever for now...

#include <memory> // shared_ptr
#include <string>

namespace chestnut::engine
{    
    enum class EAudioResourceType
    {
        SFX,
        MUSIC
    };
    
    class CAudioResource : public IResource
    {
    public:
        std::string m_audioPath;
        EAudioResourceType m_type;
        union UAudio {
            Mix_Chunk *sfx;
            Mix_Music *music;
        } m_uData;

    public:
        CAudioResource();
        ~CAudioResource();
    };


    // File types for SFX: WAVE, AIFF, RIFF, OGG, VOC
    // File types for music: WAVE, MOD, MIDI, OGG, MP3, FLAC
    // Throws ChestnutResourceLoadException on error
    std::shared_ptr< CAudioResource > loadAudioResourceFromFile( const char *audioPath, EAudioResourceType type );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_AUDIO_RESOURCE_H__