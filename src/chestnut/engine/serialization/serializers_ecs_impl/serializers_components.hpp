#pragma once

#include <nlohmann/json.hpp>

namespace chestnut::engine
{
    // forward declarations
    struct CAnimation2DComponent;
    struct CCollision2DComponent;
    struct CIdentityComponent;
    struct CKinematics2DComponent;
    struct CModel2DComponent;
    struct CRenderLayerComponent;
    struct CSpriteComponent;
    enum class ESpriteToModel2DAdjust;
    struct CTimerComponent;
    struct CTransform2DComponent;


    void to_json(nlohmann::json& j, const CAnimation2DComponent& c);
    void from_json(const nlohmann::json& j, CAnimation2DComponent& c);

    void to_json(nlohmann::json& j, const CCollision2DComponent& c);
    void from_json(const nlohmann::json& j, CCollision2DComponent& c);

    void to_json(nlohmann::json& j, const CIdentityComponent& c);
    void from_json(const nlohmann::json& j, CIdentityComponent& c);

    void to_json(nlohmann::json& j, const CKinematics2DComponent& c);
    void from_json(const nlohmann::json& j, CKinematics2DComponent& c);

    void to_json(nlohmann::json& j, const CModel2DComponent& c);
    void from_json(const nlohmann::json& j, CModel2DComponent& c);

    void to_json(nlohmann::json& j, const CRenderLayerComponent& c);
    void from_json(const nlohmann::json& j, CRenderLayerComponent& c);

    NLOHMANN_JSON_SERIALIZE_ENUM(ESpriteToModel2DAdjust, {
        {ESpriteToModel2DAdjust::NONE, "NONE"},
        {ESpriteToModel2DAdjust::SCALED, "SCALED"},
        {ESpriteToModel2DAdjust::SPANNED, "SPANNED"},
        {ESpriteToModel2DAdjust::ZOOMED, "ZOOMED"}
    });

    void to_json(nlohmann::json& j, const CSpriteComponent& c);
    void from_json(const nlohmann::json& j, CSpriteComponent& c);

    void to_json(nlohmann::json& j, const CTransform2DComponent& c);
    void from_json(const nlohmann::json& j, CTransform2DComponent& c);

} // namespace chestnut::engine


