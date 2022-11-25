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
        std::string m_animationFilePath;
        SAnimation2DSet m_animationSet;

    public:
        static tl::expected<std::shared_ptr<CAnimation2DResource>, const char *>
        loadFromFile(const char *jsonPath);
    };

} // namespace chestnut::engine
