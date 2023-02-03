#pragma once

#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/macros.hpp"

#include <string>
#include <unordered_map>
#include <vector>


struct Mix_Chunk;

namespace chestnut::engine
{
    class CHESTNUT_API CSoundBankResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS_SFX {
            "wav", "aiff", "riff", "ogg", "voc"
        };
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS_SOUND_BANKS {
            "soundbank", "bnk"
        };

        std::string m_bankName;
        std::unordered_map<std::string, Mix_Chunk *> m_mapNameToSFXHandle;

    public:
        ~CSoundBankResource() noexcept;

        static tl::expected<std::shared_ptr<CSoundBankResource>, std::string> 
        load(std::filesystem::path location) noexcept;

    private:
        CSoundBankResource(
            std::filesystem::path location,
            std::string bankName,
            std::unordered_map<std::string, Mix_Chunk *>&& sfxMap) noexcept;
    };

} // namespace chestnut::engine
