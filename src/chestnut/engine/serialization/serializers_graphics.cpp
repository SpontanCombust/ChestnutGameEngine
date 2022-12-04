#include "chestnut/engine/serialization/serializers_graphics.hpp"

#include "chestnut/engine/serialization/serializers_math.hpp"


namespace chestnut::engine
{
    void to_json(nlohmann::json& j, const CSprite& s)
    {
        j = nlohmann::json {
            {"textureResourceFilePath", s.isValid() ? s.getResource()->m_texturePath.value_or("") : ""},
            {"clipRect", s.getClippingRect()},
            {"tint", s.getTint()},
            {"tintFactor", s.getTintFactor()},
        };
    }

    void from_json(const nlohmann::json& j, CSprite& s)
    {
        std::string textureResourceFilePath;
        SRectangle clipRect;
        vec3f tint;
        float tintFactor;

        j.at("textureResourceFilePath").get_to(textureResourceFilePath);
        j.at("clipRect").get_to(clipRect);
        j.at("tint").get_to(tint);
        j.at("tintFactor").get_to(tintFactor);

        //TODO use resource manager
        auto res = CTexture2DResource::loadFromFile(textureResourceFilePath.c_str()).value();
        s.setResource(res);
        s.setClippingRect(clipRect);
        s.setTint(tint);
        s.setTintFactor(tintFactor);
    }

} // namespace chestnut::engine
