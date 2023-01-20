#pragma once

#include <nlohmann/json.hpp>

#include "chestnut/engine/misc/flags.hpp"

namespace chestnut::engine
{
    template<typename E>
    void to_json(nlohmann::json& j, const CFlags<E>& p);

    template<typename E>
    void from_json(const nlohmann::json& j, CFlags<E>& p);
    
} // namespace chestnut::engine

#include "serializers_misc.inl"