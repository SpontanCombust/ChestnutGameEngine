#pragma once

#include "chestnut/engine/graphics/sprite.hpp"

#include <nlohmann/json.hpp>

namespace chestnut::engine
{
    void to_json(nlohmann::json& j, const CSprite& s);
    void from_json(const nlohmann::json& j, CSprite& s);

} // namespace chestnut::engine
