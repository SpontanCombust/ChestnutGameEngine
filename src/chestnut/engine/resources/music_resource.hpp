#pragma once

#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/macros.hpp"

#include <string>
#include <vector>


typedef struct _Mix_Music Mix_Music;

namespace chestnut::engine
{
    class CHESTNUT_API CMusicResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS {
            "wav", "mod", "midi", "ogg", "mp3", "flac"
        };

        std::string m_musicName;
        Mix_Music *m_musicHandle;

    public:
        ~CMusicResource() noexcept;

        static tl::expected<std::shared_ptr<CMusicResource>, std::string> 
        load(std::filesystem::path location) noexcept;

    private:
        CMusicResource(
            std::filesystem::path location, 
            std::string musicName,
            Mix_Music *musicHandle) noexcept;
    };

} // namespace chestnut::engine
