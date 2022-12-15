#include "chestnut/engine/serialization/serializers_ecs_impl/serializers_components.hpp"

#include "chestnut/engine/ecs_impl/components/animation2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/collision2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/identity_component.hpp"
#include "chestnut/engine/ecs_impl/components/kinematics2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/render_layer_component.hpp"
#include "chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "chestnut/engine/ecs_impl/components/timer_component.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "chestnut/engine/serialization/serializers_math.hpp"
#include "chestnut/engine/serialization/serializers_physics.hpp"
#include "chestnut/engine/serialization/serializers_graphics.hpp"

namespace chestnut::engine
{
    using json = nlohmann::json;
    

    void to_json(nlohmann::json& j, const CAnimation2DComponent& c)
    {
        j = json {
            {"animationResourceFilePath", c.animationResource ? c.animationResource->m_animationFilePath : ""},
            {"currentAnimName", c.currentAnimName},
            {"animSpeedMultiplier", c.animSpeedMultiplier},
            {"remainingAnimLoops", c.remainingAnimLoops},
            {"isAnimPlaying", c.isAnimPlaying},
            {"isAnimPaused", c.isAnimPaused},
            {"elapsedAnimTimeSec", c.elapsedAnimTimeSec}
        };
    }

    void from_json(const nlohmann::json& j, CAnimation2DComponent& c)
    {
        std::string path;
        j.at("animationResourceFilePath").get_to(path);

        //TODO use resource manager
        // if error was returned, exception will be throws from this function
        auto res = CAnimation2DResource::loadFromFile(path.c_str()).value();

        c.animationResource = res;
        j.at("currentAnimName").get_to(c.currentAnimName);
        j.at("animSpeedMultiplier").get_to(c.animSpeedMultiplier);
        j.at("remainingAnimLoops").get_to(c.remainingAnimLoops);
        j.at("isAnimPlaying").get_to(c.isAnimPlaying);
        j.at("isAnimPaused").get_to(c.isAnimPaused);
        j.at("elapsedAnimTimeSec").get_to(c.elapsedAnimTimeSec);
    }



    void to_json(nlohmann::json& j, const CCollision2DComponent& c)
    {
        std::visit([&j](auto&& arg) {
            using T = std::decay<decltype(arg)>::type;

            if constexpr(std::is_same_v<T, CPointCollider2D>)
            {
                j = json {
                    {"variant", "point"},
                    {"collider", arg}
                };
            }
            else if constexpr(std::is_same_v<T, CBoxCollider2D>)
            {
                j = json {
                    {"variant", "box"},
                    {"collider", arg}
                };
            }
            else if constexpr(std::is_same_v<T, CCircleCollider2D>)
            {
                j = json {
                    {"variant", "point"},
                    {"collider", arg}
                };
            }

        }, c.colliderVariant);
    }

    void from_json(const nlohmann::json& j, CCollision2DComponent& c)
    {
        std::string variant;
        j.at("variant").get_to(variant);

        if(variant == "point")
        {
            c.colliderVariant = j.at("collider").get<CPointCollider2D>();
        }
        else if(variant == "box")
        {
            c.colliderVariant = j.at("collider").get<CBoxCollider2D>();
        }
        else if(variant == "circle")
        {
            c.colliderVariant = j.at("collider").get<CCircleCollider2D>();
        }
        else
        {
            throw std::exception("Unknown collider variant under key 'variant'");
        }
    }



    void to_json(nlohmann::json& j, const CIdentityComponent& c)
    {
        j = json {
            {"name", c.name}
        };
    }

    void from_json(const nlohmann::json& j, CIdentityComponent& c)
    {
        std::string s = j.at("name").get<std::string>();
        snprintf(c.name, sizeof(c.name), s.c_str());
    }



    void to_json(nlohmann::json& j, const CKinematics2DComponent& c)
    {
        j = json {
            {"linearVelocity", c.linearVelocity},
            {"linearAcceleration", c.linearAcceleration},
            {"angularVelocity", c.angularVelocity},
            {"angularAcceleration", c.angularAcceleration}
        };
    }

    void from_json(const nlohmann::json& j, CKinematics2DComponent& c)
    {
        j.at("linearVelocity").get_to(c.linearVelocity);
        j.at("linearAcceleration").get_to(c.linearAcceleration);
        j.at("angularVelocity").get_to(c.angularVelocity);
        j.at("angularAcceleration").get_to(c.angularAcceleration);
    }



    void to_json(nlohmann::json& j, const CModel2DComponent& c)
    {
        j = json {
            {"size", c.size},
            {"origin", c.origin}
        };
    }

    void from_json(const nlohmann::json& j, CModel2DComponent& c)
    {
        j.at("size").get_to(c.size);
        j.at("origin").get_to(c.origin);
    }



    void to_json(nlohmann::json& j, const CRenderLayerComponent& c)
    {
        j = json {
            {"layer", c.layer}
        };
    }

    void from_json(const nlohmann::json& j, CRenderLayerComponent& c)
    {
        j.at("layer").get_to(c.layer);
    }



    void to_json(nlohmann::json& j, const CSpriteComponent& c)
    {
        j = json {
            {"sprite", c.sprite},
            {"adjust", c.adjust},
        };
    }

    void from_json(const nlohmann::json& j, CSpriteComponent& c)
    {
        j.at("sprite").get_to(c.sprite);
        j.at("adjust").get_to(c.adjust);
    }



    void to_json(json& j, const CTransform2DComponent& c)
    {
        j = json {
            {"position", c.position},
            {"scale", c.scale},
            {"rotation", c.rotation}
        };
    }

    void from_json(const json& j, CTransform2DComponent& c)
    {
        j.at("position").get_to(c.position);
        j.at("scale").get_to(c.scale);
        j.at("rotation").get_to(c.rotation);
    }

} // namespace ns
