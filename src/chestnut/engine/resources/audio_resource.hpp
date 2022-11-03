#ifndef __CHESTNUT_ENGINE_AUDIO_RESOURCE_H__
#define __CHESTNUT_ENGINE_AUDIO_RESOURCE_H__

#include "chestnut/engine/macros.hpp"
#include "resource.hpp"

#include <SDL_mixer.h> //FIXME It'd better if this wasn't here, but whatever for now...

#include <string>

namespace chestnut::engine
{    
    enum class EAudioResourceType
    {
        SFX,
        MUSIC
    };
    
    class CHESTNUT_API CAudioResource : public IResource
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
        static tl::expected<std::shared_ptr<CAudioResource>, const char *> loadFromFile(const char *audioPath, EAudioResourceType type) noexcept;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_AUDIO_RESOURCE_H__