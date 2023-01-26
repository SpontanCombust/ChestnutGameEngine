#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/resources/animation2d_resource.hpp"
#include "chestnut/engine/resources/entity_template_resource.hpp"
#include "chestnut/engine/resources/font_resource.hpp"
#include "chestnut/engine/resources/image_data_resource.hpp"
#include "chestnut/engine/resources/music_resource.hpp"
#include "chestnut/engine/resources/scene_resource.hpp"
#include "chestnut/engine/resources/shader_program_resource.hpp"
#include "chestnut/engine/resources/sound_bank_resource.hpp"
#include "chestnut/engine/resources/texture2d_resource.hpp"

#include <nlohmann/json.hpp>

namespace chestnut::engine
{
    // only source location information is needed for serializing resource objects, so base class is enough
    void CHESTNUT_API to_json(nlohmann::json& j, const std::shared_ptr<IResource>& r);

    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CAnimation2DResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CEntityTemplateResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CFontResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CImageDataResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CMusicResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CSceneResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CShaderProgramResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CSoundBankResource>& r);
    void CHESTNUT_API from_json(const nlohmann::json& j, std::shared_ptr<CTexture2DResource>& r);

} // namespace chestnut::engine
