#include "chestnut/engine/serialization/serializers_graphics.hpp"

#include "chestnut/engine/serialization/serializers_math.hpp"
#include "chestnut/engine/serialization/serializers_resources.hpp"


namespace chestnut::engine
{
    void to_json(nlohmann::json& j, const CSprite& s)
    {
        j = nlohmann::json {
            {"textureResource", s.getResource()},
            {"clipRect", s.getClippingRect()},
            {"tint", s.getTint()},
            {"tintFactor", s.getTintFactor()},
        };
    }

    void from_json(const nlohmann::json& j, CSprite& s)
    {
        std::shared_ptr<CTexture2DResource> textureResource;
        SRectangle clipRect;
        vec3f tint;
        float tintFactor;

        j.at("textureResource").get_to(textureResource);
        j.at("clipRect").get_to(clipRect);
        j.at("tint").get_to(tint);
        j.at("tintFactor").get_to(tintFactor);

        if(textureResource) 
        {
            s.setResource(textureResource);
        }
        s.setClippingRect(clipRect);
        s.setTint(tint);
        s.setTintFactor(tintFactor);
    }

} // namespace chestnut::engine
