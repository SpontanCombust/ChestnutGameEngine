#include "chestnut/engine/resources/sound_bank_resource.hpp"

#include "chestnut/engine/init.hpp"
#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"

#include <SDL_mixer.h>
#include <nlohmann/json.hpp>

#include <cassert>
#include <fstream>

namespace chestnut::engine
{ 
    CSoundBankResource::CSoundBankResource(
            std::filesystem::path location,
            std::string bankName,
            std::unordered_map<std::string, Mix_Chunk *>&& sfxMap) noexcept
    : IResource(location),
      m_bankName(bankName),
      m_mapNameToSFXHandle(sfxMap)
    {

    }

    CSoundBankResource::~CSoundBankResource() noexcept
    {
        for(auto& [_, chunk] : m_mapNameToSFXHandle)
        {
            Mix_FreeChunk(chunk);
        }
    }

    tl::expected<std::shared_ptr<CSoundBankResource>, std::string> 
    CSoundBankResource::load(std::filesystem::path location) noexcept
    {
        assert(chestnutWasInit() && "Can't load this type of resource without first initializing dependency libraries! Use chestnutInit() first!");

        LOG_INFO("Loading soundbank resource from file " << location << "...");

        if(!std::filesystem::exists(location))
        {
            return tl::make_unexpected("File does not exist: " + location.string());
        }

        auto [ext, supported] = isExtensionSupported(location, SUPPORTED_FILE_EXTENSIONS_SOUND_BANKS);
        if(!supported)
        {
            return tl::make_unexpected("Unsupported file type: " + ext);
        }


        std::ifstream f(location);
        if(!f)
        {
            return tl::make_unexpected("File open error");
        }


        std::unordered_map<std::string, Mix_Chunk *> sfxMap;

        try
        {
            auto bnkJson = nlohmann::json::parse(f); 
            
            for(auto [alias, assetPath] : bnkJson.items())
            {
                auto absAssetPath = assetPathToAbsolute(assetPath.get<std::filesystem::path>());

                if(!std::filesystem::exists(absAssetPath))
                {
                    return tl::make_unexpected("Soundbank audio does not exist: " + absAssetPath.string());
                }

                auto [extSfx, supportedSfx] = isExtensionSupported(absAssetPath, SUPPORTED_FILE_EXTENSIONS_SFX);
                if(!supportedSfx)
                {
                    return tl::make_unexpected("Unsupported soundbank audio file type: " + extSfx);
                }

                Mix_Chunk *sfx = Mix_LoadWAV(absAssetPath.string().c_str());
                if(!sfx)
                {
                    return tl::make_unexpected("Audio file from " + absAssetPath.string() + " loading error: " + std::string(Mix_GetError()));
                }

                sfxMap[alias] = sfx;
            }
        }
        catch(const std::exception& e)
        {
            return tl::make_unexpected("File parsing error: " + std::string(e.what()));
        }


        return std::shared_ptr<CSoundBankResource>(new CSoundBankResource(
            location,
            location.stem().string(),
            std::move(sfxMap)
        ));
    }
    
} // namespace chestnut::engine
