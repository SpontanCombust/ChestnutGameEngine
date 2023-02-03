#include <catch2/catch.hpp>

#include "chestnut/engine/init.hpp"
#include "chestnut/engine/main/window.hpp"
#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"
#include "chestnut/engine/resources/image_data_resource.hpp"
#include "chestnut/engine/resources/texture2d_resource.hpp"
#include "chestnut/engine/resources/shader_program_resource.hpp"
#include "chestnut/engine/resources/animation2d_resource.hpp"
#include "chestnut/engine/resources/font_resource.hpp"
#include "chestnut/engine/resources/music_resource.hpp"
#include "chestnut/engine/resources/sound_bank_resource.hpp"
#include "chestnut/engine/resources/entity_template_resource.hpp"
#include "chestnut/engine/ecs_impl/components/identity_component.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "chestnut/engine/resources/scene_resource.hpp"

using namespace chestnut::engine;

TEST_CASE("Resources - image data resource test")
{
    auto p = assetPathToAbsolute("testing/images/awesomeface.png");
    auto exp = CImageDataResource::load(p);
    REQUIRE(exp.has_value());

    auto r = *exp;
    REQUIRE(r->m_location == p);
    REQUIRE(r->m_width == 512);
    REQUIRE(r->m_height == 512);
    REQUIRE(r->m_numChannels == 4);
}

TEST_CASE("Resources - texture resource test")
{
    chestnutInit();
    {
        auto w = CWindow(CWindowAttribs("").show(false));

        // texture can be loaded either directly from image file or based on definition json
        auto p1 = assetPathToAbsolute("testing/images/player_sheet_orig.png");
        auto p2 = assetPathToAbsolute("testing/textures/player_sheet_orig.texture");

        auto exp1 = CTexture2DResource::load(p1);
        REQUIRE(exp1.has_value());

        auto r1 = *exp1;
        REQUIRE(r1->m_location == p1);
        REQUIRE(r1->m_width == 256);
        REQUIRE(r1->m_height == 128);


        auto exp2 = CTexture2DResource::load(p2);
        REQUIRE(exp2.has_value());

        auto r2 = *exp1;
        REQUIRE(r2->m_location == p1);
        REQUIRE(r2->m_width == 256);
        REQUIRE(r2->m_height == 128);
    }
    chestnutQuit();
}

TEST_CASE("Resources - shader resource test")
{
    chestnutInit();
    {
        CWindow window(CWindowAttribs("").show(false));

        auto p = assetPathToAbsolute("testing/shaders/testShader.shader");
        auto p_vs = assetPathToAbsolute("testing/shaders/testShader.vs");
        auto p_fs = assetPathToAbsolute("testing/shaders/testShader.fs");
        auto exp = CShaderProgramResource::load(p);
        REQUIRE(exp.has_value());

        auto r = *exp;
        REQUIRE(r->m_location == p);
        REQUIRE(r->m_vertexShaderPath == p_vs);
        REQUIRE(r->m_fragmentShaderPath == p_fs);
    }
    chestnutQuit();
}

TEST_CASE("Resources - animation resource test")
{
    auto p = assetPathToAbsolute("testing/animations/player_sheet_orig.anim");
    auto exp = CAnimation2DResource::load(p);
    REQUIRE(exp.has_value());
    auto r = *exp;

    REQUIRE(r->m_location == p);
    REQUIRE(r->m_animationSet.defaultAnimFrameIndex == 0);
    REQUIRE(r->m_animationSet.vecKeyFrameClipRects[0] == SRectangle(0.5, 0.5, 32.0, 32.0));
    REQUIRE(r->m_animationSet.vecKeyFrameClipRects[31] == SRectangle(224.5, 96.5, 32.0, 32.0));
    REQUIRE(r->m_animationSet.mapAnimNameToAnimData["walk_down"].name == "walk_down"); // if doesn't exist will have default name as empty string
    REQUIRE(r->m_animationSet.mapAnimNameToAnimData["walk_up"].name == "walk_up");
    REQUIRE(r->m_animationSet.mapAnimNameToAnimData["walk_left"].name == "walk_left");
    REQUIRE(r->m_animationSet.mapAnimNameToAnimData["walk_right"].name == "walk_right");
    REQUIRE(r->m_animationSet.mapAnimNameToAnimData["walk_right"].duration == 1.0);
    REQUIRE(r->m_animationSet.mapAnimNameToAnimData["walk_right"].vecFrameIndices == std::vector<unsigned int>{24, 25, 26, 27, 28, 29, 30, 31});
}

TEST_CASE("Resources - font resource test")
{
    // SDL_TTF needs to be initialized and have available OpenGL context
    chestnutInit();
    {
        CWindow window(CWindowAttribs("").show(false));

        auto p = assetPathToAbsolute("testing/fonts/arial.ttf");
        auto exp = CFontResource::load(p);
        REQUIRE(exp.has_value());

        auto r = *exp;
        REQUIRE(r->m_location == p);
        REQUIRE(r->loadConfig(20, EFontStyle::BOLD));
    }
    chestnutQuit();
}

TEST_CASE("Resources - music resource test")
{
    chestnutInit();
    {
        auto p = assetPathToAbsolute("testing/audio/dramatic-music.mp3");
        auto exp = CMusicResource::load(p);
        REQUIRE(exp.has_value());

        auto r = *exp;
        REQUIRE(r->m_location == p);
        REQUIRE(r->m_musicName == "dramatic-music");
        REQUIRE(r->m_musicHandle != nullptr);
    }
    chestnutQuit();
}

TEST_CASE("Resources - soundbank resource test")
{
    chestnutInit();
    {
        auto p = assetPathToAbsolute("testing/audio/sounds.bnk");
        auto exp = CSoundBankResource::load(p);
        REQUIRE(exp.has_value());

        auto r = *exp;
        REQUIRE(r->m_location == p);
        REQUIRE(r->m_bankName == "sounds");
        REQUIRE(r->m_mapNameToSFXHandle.size() == 3);
        REQUIRE(r->m_mapNameToSFXHandle["explosion"] != nullptr);
        REQUIRE(r->m_mapNameToSFXHandle["hurt"] != nullptr);
        REQUIRE(r->m_mapNameToSFXHandle["sword-slash"] != nullptr);
    }
    chestnutQuit();
}

TEST_CASE("Resources - entity template resource test")
{
    chestnutInit();
    CWindow window(CWindowAttribs("").show(false));
    CEngine::createInstance(window);
    {
        auto p = assetPathToAbsolute("testing/entities/testEntity.ent");
        auto exp = CEntityTemplateResource::load(p);
        REQUIRE(exp.has_value());

        auto r = *exp;
        REQUIRE(r->m_location == p);
        

        auto expEnt = r->createEntity();
        REQUIRE(expEnt.has_value());

        auto ent = *expEnt;
        auto& w = CEngine::getInstance().getEntityWorld();
        REQUIRE(w.hasComponent<CIdentityComponent>(ent));
        REQUIRE(w.hasComponent<CTransform2DComponent>(ent));
        REQUIRE(w.hasComponent<CSpriteComponent>(ent));
    }
    CEngine::deleteInstance();
    chestnutQuit();
}

TEST_CASE("Resources - scene resource test")
{
    //TODO TEST scene resource test
}
