#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/graphics/animation2d.hpp"

#include <vector>


namespace chestnut::engine
{
    class CHESTNUT_API CAnimation2DResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS = {
            "anim", "animation"
        };

        SAnimation2DSet m_animationSet;

    public:
        static tl::expected<std::shared_ptr<CAnimation2DResource>, std::string>
        load(std::filesystem::path animPath);

    private:
        CAnimation2DResource(std::filesystem::path location) noexcept;
    };

} // namespace chestnut::engine
