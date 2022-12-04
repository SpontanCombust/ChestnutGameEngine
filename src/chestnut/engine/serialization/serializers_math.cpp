#include "chestnut/engine/serialization/serializers_math.hpp"

namespace chestnut::engine {

    void to_json(nlohmann::json& j, const vec2f& v)
    {
        j = nlohmann::json {
            {"x", v.x},
            {"y", v.y},
        };
    }

    void from_json(const nlohmann::json& j, vec2f& v)
    {
        j.at("x").get_to(v.x);
        j.at("y").get_to(v.y);
    }


    void to_json(nlohmann::json& j, const vec2i& v)
    {
        j = nlohmann::json {
            {"x", v.x},
            {"y", v.y},
        };
    }

    void from_json(const nlohmann::json& j, vec2i& v)
    {
        j.at("x").get_to(v.x);
        j.at("y").get_to(v.y);
    }


    void to_json(nlohmann::json& j, const vec3f& v)
    {
        j = nlohmann::json {
            {"x", v.x},
            {"y", v.y},
            {"z", v.z},
        };
    }

    void from_json(const nlohmann::json& j, vec3f& v)
    {
        j.at("x").get_to(v.x);
        j.at("y").get_to(v.y);
        j.at("z").get_to(v.z);
    }

    void to_json(nlohmann::json& j, const SRectangle& r)
    {
        j = nlohmann::json {
            {"x", r.x},
            {"y", r.y},
            {"w", r.w},
            {"h", r.h},
        };
    }

    void from_json(const nlohmann::json& j, SRectangle& r)
    {
        j.at("x").get_to(r.x);
        j.at("y").get_to(r.y);
        j.at("w").get_to(r.w);
        j.at("h").get_to(r.h);
    }

} // namespace chestnut::engine
