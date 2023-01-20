#pragma once

#include <nlohmann/json.hpp>

#include "chestnut/engine/physics/collider_attributes.hpp"
#include "chestnut/engine/physics/collider2d.hpp"

namespace chestnut::engine
{
    NLOHMANN_JSON_SERIALIZE_ENUM(EColliderActivity, {
        {EColliderActivity::STATIC, "STATIC"},
        {EColliderActivity::DYNAMIC, "DYNAMIC"}
    });
    
    NLOHMANN_JSON_SERIALIZE_ENUM(ECollisionPolicy, {
        {ECollisionPolicy::AFFECTED, "AFFECTED"},
        {ECollisionPolicy::AFFECTING, "AFFECTING"},
        {ECollisionPolicy::TRIGGER, "TRIGGER"}
    });

    void to_json(nlohmann::json& j, const CPointCollider2D& p);
    void from_json(const nlohmann::json& j, CPointCollider2D& p);

    void to_json(nlohmann::json& j, const CBoxCollider2D& b);
    void from_json(const nlohmann::json& j, CBoxCollider2D& b);

    void to_json(nlohmann::json& j, const CCircleCollider2D& c);
    void from_json(const nlohmann::json& j, CCircleCollider2D& c);
        
} // namespace chestnut::engine
