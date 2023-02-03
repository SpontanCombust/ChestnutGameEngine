#pragma once

#include <nlohmann/json.hpp>

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/vector3.hpp"
#include "chestnut/engine/maths/rectangle.hpp"

namespace chestnut::engine {

    void CHESTNUT_API to_json(nlohmann::json& j, const vec2f& v);
    void CHESTNUT_API from_json(const nlohmann::json& j, vec2f& v);

    void CHESTNUT_API to_json(nlohmann::json& j, const vec2i& v);
    void CHESTNUT_API from_json(const nlohmann::json& j, vec2i& v);

    void CHESTNUT_API to_json(nlohmann::json& j, const vec3f& v);
    void CHESTNUT_API from_json(const nlohmann::json& j, vec3f& v);

    void CHESTNUT_API to_json(nlohmann::json& j, const SRectangle& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, SRectangle& r);

} // namespace chestnut::engine
