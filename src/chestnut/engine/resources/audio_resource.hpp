#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"

#include <SDL_mixer.h> //FIXME It'd better if this wasn't here, but whatever for now...

#include <string>

namespace chestnut::engine
{    
    enum class EAudioResourceType
    {
        SFX,
        MUSIC
    };
    
    //TODO divide into music and sound bank resources
    class CHESTNUT_API CAudioResource
    {
    public:
        std::string m_audioPath;
        EAudioResourceType m_type;
        union UAudio {
            Mix_Chunk *sfx;
            Mix_Music *music;
        } m_uData;

    public:
        CAudioResource() noexcept;
        ~CAudioResource() noexcept;

        // File types for SFX: WAVE, AIFF, RIFF, OGG, VOC
        // File types for music: WAVE, MOD, MIDI, OGG, MP3, FLAC
        static tl::expected<std::shared_ptr<CAudioResource>, const char *> 
        loadFromFile(const char *audioPath, EAudioResourceType type) noexcept;
    };

} // namespace chestnut::engine

