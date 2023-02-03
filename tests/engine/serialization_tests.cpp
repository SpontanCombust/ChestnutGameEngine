#include <catch2/catch.hpp>

#include "chestnut/engine/init.hpp"
#include "chestnut/engine/main/window.hpp"
#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"
#include "chestnut/engine/serialization/serializers_ecs_impl/serializers_components.hpp"
#include "chestnut/engine/serialization/serializers_graphics.hpp"
#include "chestnut/engine/serialization/serializers_math.hpp"
#include "chestnut/engine/serialization/serializers_misc.hpp"
#include "chestnut/engine/serialization/serializers_physics.hpp"
#include "chestnut/engine/serialization/serializers_resources.hpp"
#include "chestnut/engine/ecs_impl/components/animation2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/collision2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/identity_component.hpp"
#include "chestnut/engine/ecs_impl/components/kinematics2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/render_layer_component.hpp"
#include "chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "chestnut/engine/ecs_impl/components/tag_component.hpp"
#include "chestnut/engine/ecs_impl/components/timer_component.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"

using namespace chestnut::engine;
using json = nlohmann::json;
using namespace nlohmann::literals;

TEST_CASE("Serialization - math")
{
    SECTION("vec2f")
    {
        vec2f v {3.14f, 4.20003f};

        json vj = {
            {"x", 3.14f},
            {"y", 4.20003f}
        };

        REQUIRE(json(v) == vj);
        REQUIRE(vj.get<vec2f>() == v);
    }

    SECTION("vec2i")
    {
        vec2i v {3, -12};

        json vj = {
            {"x", 3},
            {"y", -12}
        };

        REQUIRE(json(v) == vj);
        REQUIRE(vj.get<vec2i>() == v);
    }

    SECTION("vec3i")
    {
        vec3f v {3.14f, 4.20003f, 60.09f};

        json vj = {
            {"x", 3.14f},
            {"y", 4.20003f},
            {"z", 60.09f}
        };

        REQUIRE(json(v) == vj);
        REQUIRE(vj.get<vec3f>() == v);
    }

    SECTION("SRectangle")
    {
        SRectangle r {-1.2f, 2.3f, -4.05f, 6.78f};

        json rj {
            {"x", -1.2f},
            {"y", 2.3f},
            {"w", -4.05f},
            {"h", 6.78f}
        };

        REQUIRE(json(r) == rj);
        REQUIRE(rj.get<SRectangle>() == r);
    }
}



enum class E {
    VAL0,
    VAL1,
    VAL2,
    VAL3
};

NLOHMANN_JSON_SERIALIZE_ENUM(E,{
    {E::VAL0, "VAL0"},
    {E::VAL1, "VAL1"},
    {E::VAL2, "VAL2"},
    {E::VAL3, "VAL3"},
});

TEST_CASE("Serialization - misc")
{
    SECTION("CFlags<T>")
    {
        CFlags<E> f;
        json fj;


        f = {};
        fj = "[]"_json;

        REQUIRE(json(f) == fj);
        REQUIRE(fj.get<CFlags<E>>() == f);


        f = {E::VAL1};
        fj = R"(["VAL1"])"_json;

        REQUIRE(json(f) == fj);
        REQUIRE(fj.get<CFlags<E>>() == f);


        f = {E::VAL0, E::VAL2, E::VAL3};
        fj = R"(["VAL0", "VAL2", "VAL3"])"_json;

        REQUIRE(json(f) == fj);
        REQUIRE(fj.get<CFlags<E>>() == f);
    }
}



TEST_CASE("Serialization - physics")
{
    SECTION("EColliderActivity")
    {
        EColliderActivity e; 
        json ej; 


        e = EColliderActivity::STATIC;
        ej = "STATIC";

        REQUIRE(json(e) == ej);
        REQUIRE(ej.get<EColliderActivity>() == e);


        e = EColliderActivity::DYNAMIC;
        ej = "DYNAMIC";
        
        REQUIRE(json(e) == ej);
        REQUIRE(ej.get<EColliderActivity>() == e);
    }

    SECTION("ECollisionPolicy")
    {
        ECollisionPolicy e; 
        json ej; 


        e = ECollisionPolicy::AFFECTED;
        ej = "AFFECTED";

        REQUIRE(json(e) == ej);
        REQUIRE(ej.get<ECollisionPolicy>() == e);


        e = ECollisionPolicy::AFFECTING;
        ej = "AFFECTING";

        REQUIRE(json(e) == ej);
        REQUIRE(ej.get<ECollisionPolicy>() == e);


        e = ECollisionPolicy::TRIGGER;
        ej = "TRIGGER";

        REQUIRE(json(e) == ej);
        REQUIRE(ej.get<ECollisionPolicy>() == e);
    }

    SECTION("CPointCollider2D")
    {
        CPointCollider2D c;
        c.setActivity(EColliderActivity::STATIC);
        c.setPolicyFlags({});
        c.setPosition({1.23f, -45.6f});
        c.setScale({-0.78f, 90.10f});

        json cj {
            {"activity", "STATIC"},
            {"policyFlags", CFlags<ECollisionPolicy>{}},
            {"position", vec2f{1.23f, -45.6f}},
            {"scale", vec2f{-0.78f, 90.10f}}
        };


        REQUIRE(json(c) == cj);

        CPointCollider2D c_;
        cj.get_to(c_);
        REQUIRE(c_.getActivity() == c.getActivity());
        REQUIRE(c_.getPolicyFlags() == c.getPolicyFlags());
        REQUIRE(c_.getPosition() == c.getPosition());
        REQUIRE(c_.getScale() == c.getScale());
    }

    SECTION("CBoxCollider2D")
    {
        CBoxCollider2D c;
        c.setActivity(EColliderActivity::DYNAMIC);
        c.setPolicyFlags({ECollisionPolicy::AFFECTED, ECollisionPolicy::AFFECTING});
        c.setPosition({5.4f, 3.2f});
        c.setScale({-2.3f, -4.5f});
        c.setSize({6.7f, -9.8f});

        json cj {
            {"activity", "DYNAMIC"},
            {"policyFlags", CFlags<ECollisionPolicy>{ECollisionPolicy::AFFECTED, ECollisionPolicy::AFFECTING}},
            {"position", vec2f{5.4f, 3.2f}},
            {"scale", vec2f{-2.3f, -4.5f}},
            {"size", vec2f{6.7f, -9.8f}}
        };


        REQUIRE(json(c) == cj);

        CBoxCollider2D c_;
        cj.get_to(c_);
        REQUIRE(c_.getActivity() == c.getActivity());
        REQUIRE(c_.getPolicyFlags() == c.getPolicyFlags());
        REQUIRE(c_.getPosition() == c.getPosition());
        REQUIRE(c_.getScale() == c.getScale());
        REQUIRE(c_.getSize() == c.getSize());
    }

    SECTION("CircleCollider2D")
    {
        CCircleCollider2D c;
        c.setActivity(EColliderActivity::DYNAMIC);
        c.setPolicyFlags({ECollisionPolicy::AFFECTED, ECollisionPolicy::AFFECTING});
        c.setPosition({1.1f, -2.2f});
        c.setScale({-3.3f, 4.4f});
        c.setRadius(5.5f);

        json cj {
            {"activity", "DYNAMIC"},
            {"policyFlags", CFlags<ECollisionPolicy>{ECollisionPolicy::AFFECTED, ECollisionPolicy::AFFECTING}},
            {"position", vec2f{1.1f, -2.2f}},
            {"scale", vec2f{-3.3f, 4.4f}},
            {"radius", 5.5f}
        };


        REQUIRE(json(c) == cj);

        CCircleCollider2D c_;
        cj.get_to(c_);
        REQUIRE(c_.getActivity() == c.getActivity());
        REQUIRE(c_.getPolicyFlags() == c.getPolicyFlags());
        REQUIRE(c_.getPosition() == c.getPosition());
        REQUIRE(c_.getScale() == c.getScale());
        REQUIRE(c_.getRadius() == c.getRadius());
    }
}



TEST_CASE("Serialization - resources")
{ 
    //TODO TEST Serialization - resources

    SECTION("CAnimation2DResource")
    {
        
    }

    SECTION("CEntityTemplateResource")
    {

    }

    SECTION("CFontResource")
    {

    }

    SECTION("CImageDataResource")
    {

    }

    SECTION("CMusicResource")
    {

    }

    SECTION("CSceneResource")
    {

    }

    SECTION("CShaderProgramResource")
    {

    }

    SECTION("CSoundBankResource")
    {

    }

    SECTION("CTexture2DResource")
    {

    }
}



TEST_CASE("Serialization - graphics")
{
    //TODO TEST Serialization - graphics

    SECTION("CSprite")
    {

    }
}



TEST_CASE("Serialization - components")
{
    //TODO TEST Serialization - components

    SECTION("CAnimation2DComponent")
    {
        
    }

    SECTION("CCollision2DComponent")
    {

    }

    SECTION("CIdentityComponent")
    {

    }

    SECTION("CKinematics2DComponent")
    {

    }

    SECTION("CModel2DComponent")
    {

    }

    SECTION("CRenderLayerComponent")
    {

    }

    SECTION("CSpriteComponent")
    {

    }

    SECTION("CTagComponent")
    {

    }

    SECTION("CTransform2DComponent")
    {
        CTagComponent c;
        json cj = {};

        REQUIRE(json(c) == cj);
        // REQUIRE(cj.get<CTagComponent>() == c);
    }
}