#include "chestnut/engine/resources/music_resource.hpp"

#include "chestnut/engine/init.hpp"
#include "chestnut/engine/debug/log.hpp"

#include <SDL_mixer.h>

#include <cassert>


namespace chestnut::engine
{    
    CMusicResource::CMusicResource(std::filesystem::path location, std::string musicName, Mix_Music *musicHandle) noexcept
    : IResource(location),
      m_musicName(musicName),
      m_musicHandle(musicHandle)
    {
        
    }

    CMusicResource::~CMusicResource() noexcept
    {
        Mix_FreeMusic(m_musicHandle);
    }

    tl::expected<std::shared_ptr<CMusicResource>, std::string> 
    CMusicResource::load(std::filesystem::path location) noexcept
    {
        assert(chestnutWasInit() && "Can't load this type of resource without first initializing dependency libraries! Use chestnutInit() first!");

        LOG_INFO("Loading music resource from file " << location << "...");

        if(!std::filesystem::exists(location))
        {
            return tl::make_unexpected("File does not exist: " + location.string());
        }

        auto [ext, supported] = isExtensionSupported(location, SUPPORTED_FILE_EXTENSIONS);
        if(!supported)
        {
            return tl::make_unexpected("Unsupported file type: " + ext);
        }

        
        Mix_Music *handle = Mix_LoadMUS(location.string().c_str());

        if(!handle)
        {
            return tl::make_unexpected("File loading error: " + std::string(Mix_GetError()));
        }

        return std::shared_ptr<CMusicResource>(new CMusicResource(
            location,
            location.stem().string(),
            handle
        ));
    }

} // namespace chestnut::engine
