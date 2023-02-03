#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/sprite.hpp"

#include <nlohmann/json.hpp>

namespace chestnut::engine
{
    void CHESTNUT_API to_json(nlohmann::json& j, const CSprite& s);
    void CHESTNUT_API from_json(const nlohmann::json& j, CSprite& s);

} // namespace chestnut::engine
