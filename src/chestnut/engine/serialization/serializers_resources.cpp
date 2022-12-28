#include "chestnut/engine/serialization/serializers_resources.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"
#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/debug/component_rtti.hpp"

namespace chestnut::engine
{
    void to_json(nlohmann::json& j, const std::shared_ptr<IResource>& r)
    {
        if(!r || !r->m_location)
        {
            j = nullptr;
        }
        else
        {
            auto [path, isInAssets] = assetPathFromAbsolute(r->m_location.value());
            if(!isInAssets)
            {
                LOG_WARNING("Serialized resource is using an asset that is located outside of assets/ directory: " << path);
            }

            j = path;
        }
    }


    template<class R>
    void resource_from_json(const nlohmann::json& j, std::shared_ptr<R>& r)
    {
        if(j.is_null())
        {
            LOG_WARNING("Null resource path");
            return;
        }

        std::filesystem::path path;
        j.get_to(path);

        path = assetPathToAbsolute(path);

        r = CEngine::getInstance()
        .getResourceManager()
        .getOrLoadResource<R>(
            assetPathToAbsolute(path)
        ).value(); // from_json functions are throwing, so we can try get the value here
    }

    void from_json(const nlohmann::json& j, std::shared_ptr<CAnimation2DResource>& r)
    {
        resource_from_json(j, r);
    }

    // void from_json(const nlohmann::json& j, std::shared_ptr<CAudioResource>& r)
    // {

    // }

    void from_json(const nlohmann::json& j, std::shared_ptr<CFontResource>& r)
    {
        resource_from_json(j, r);
    }

    void from_json(const nlohmann::json& j, std::shared_ptr<CImageDataResource>& r)
    {
        resource_from_json(j, r);
    }

    void from_json(const nlohmann::json& j, std::shared_ptr<CSceneResource>& r)
    {
        resource_from_json(j, r);
    }

    void from_json(const nlohmann::json& j, std::shared_ptr<CShaderProgramResource>& r)
    {
        resource_from_json(j, r);
    }

    void from_json(const nlohmann::json& j, std::shared_ptr<CTexture2DResource>& r)
    {
        resource_from_json(j, r);
    }

} // namespace chestnut::engine
