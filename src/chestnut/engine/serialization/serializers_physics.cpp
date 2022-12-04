#include "chestnut/engine/serialization/serializers_physics.hpp"

#include "chestnut/engine/serialization/serializers_math.hpp"


namespace chestnut::engine
{
    using json = nlohmann::json;
    

    static void to_json(nlohmann::json& j, const CCollider2D& p)
    {
        j["activity"] = p.getActivity();
        j["policyFlags"] = p.getPolicyFlags();
        j["position"] = p.getPosition();
        j["scale"] = p.getScale();
    }

    static void from_json(const nlohmann::json& j, CCollider2D& p)
    {
        p.setActivity(j.at("activity").get<EColliderActivity>());
        p.setPolicyFlags(j.at("policyFlags").get<ECollisionPolicyFlags>());
        p.setPosition(j.at("position").get<vec2f>());
        p.setScale(j.at("scale").get<vec2f>());
    }



    void to_json(nlohmann::json& j, const CPointCollider2D& p)
    {
        j = json {};
        to_json(j, (CCollider2D&)p);
    }

    void from_json(const nlohmann::json& j, CPointCollider2D& p)
    {
        from_json(j, (CCollider2D&)p);
    }



    void to_json(nlohmann::json& j, const CBoxCollider2D& b)
    {
        j = json {};
        to_json(j, (CCollider2D&)b);
        j["size"] = b.getSize();
    }

    void from_json(const nlohmann::json& j, CBoxCollider2D& b)
    {
        from_json(j, (CCollider2D&)b);
        b.setSize(j.at("size").get<vec2f>());
    }



    void to_json(nlohmann::json& j, const CCircleCollider2D& c)
    {
        j = json {};
        to_json(j, (CCollider2D&)c);
        j["radius"] = c.getRadius();
    }

    void from_json(const nlohmann::json& j, CCircleCollider2D& c)
    {
        from_json(j, (CCollider2D&)c);
        c.setRadius(j.at("radius").get<float>());
    }

} // namespace chestnut::engine
