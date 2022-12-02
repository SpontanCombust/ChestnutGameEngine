#include "chestnut/engine/resources/animation2d_resource.hpp"
#include "chestnut/engine/debug/log.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <array>
#include <fstream>
#include <unordered_map>
#include <vector>

namespace chestnut::engine
{
    const char * const KEY_vecKeyFrameClipRects = "keyFrameClippingRectangles";
    const char * const KEY_mapAnimNameToAnimData = "animationDefinitions";
    const char * const KEY_mapAnimNameToAnimData_name = "name";
    const char * const KEY_mapAnimNameToAnimData_duration = "duration";
    const char * const KEY_mapAnimNameToAnimData_vecFrameIndices = "frameIndices";
    const char * const KEY_defaultAnimFrameIndex = "defaultAnimationFrameIndex";

    std::vector<SRectangle> parseClippingRects(json j)
    {
        std::array<float, 4> clippingRectBuff;
        std::vector<SRectangle> vecClippingRects;

        json obj = j.at(KEY_vecKeyFrameClipRects);
        for(const auto& arr : obj)
        {
            arr.get_to(clippingRectBuff);
            vecClippingRects.push_back({clippingRectBuff[0], clippingRectBuff[1], clippingRectBuff[2], clippingRectBuff[3]});
        }

        return vecClippingRects;
    }

    std::unordered_map<std::string, SAnimation2DDefinition> parseAnimationDefinitions(json j)
    {
        std::string animNameBuff;
        std::vector<unsigned int> vecFrameIndicesBuff;
        std::unordered_map<std::string, SAnimation2DDefinition> mapAnimData;

        json obj = j.at(KEY_mapAnimNameToAnimData);
        for(const auto& o : obj)
        {
            SAnimation2DDefinition animData;

            o.at(KEY_mapAnimNameToAnimData_name).get_to(animNameBuff);
            animData.name = animNameBuff;

            animData.duration = o.at(KEY_mapAnimNameToAnimData_duration).get<float>();

            o.at(KEY_mapAnimNameToAnimData_vecFrameIndices).get_to(vecFrameIndicesBuff);
            animData.vecFrameIndices = vecFrameIndicesBuff;

            mapAnimData[animData.name] = animData;
        }

        return mapAnimData;
    }

    unsigned int parseDefaultAnimIndex(json j)
    {
        try
        {
            auto i = j.at(KEY_defaultAnimFrameIndex).get<unsigned int>();
            return i;
        }
        catch(const std::exception& e)
        {
            return 0;
        }  
    }

    void validateDefaultFrameIndex(
        unsigned int& defaultFrameIndex,
        unsigned int keyframesTotalNum
    )
    {
        if(defaultFrameIndex >= keyframesTotalNum)
        {
            LOG_WARNING("Default keyframe index out of range. Setting to default value 0...");
            defaultFrameIndex = 0;
        }
    }

    void validateDefinitions(
        std::unordered_map<std::string, SAnimation2DDefinition>& definitions, 
        unsigned int keyframesTotalNum,
        unsigned int defaultKeyFrameIdx)
    {
        for(auto& [_, def] : definitions)
        {
            bool foundInvalidIndex = false;

            for (size_t i = 0; i < def.vecFrameIndices.size(); i++)
            {
                if(def.vecFrameIndices[i] >= keyframesTotalNum)
                {
                    def.vecFrameIndices[i] = defaultKeyFrameIdx;
                    foundInvalidIndex = true;
                }
            }

            if(foundInvalidIndex)
            {
                LOG_WARNING("Found keyframe indices out of range in animation \"" << def.name << "\". Setting them to default index...");
            }
        }
    }

    tl::expected<std::shared_ptr<CAnimation2DResource>, std::string>    
    CAnimation2DResource::loadFromFile(const char *jsonPath) 
    {
        LOG_INFO( "Loading animation data from file: " << jsonPath << "..." );

        std::ifstream stream(jsonPath);
        if(!stream)
        {
            LOG_ERROR("Failed to open animation data from file " << jsonPath);
            return tl::make_unexpected("Failed to open the file");
        }

        try
        {
            json j = json::parse(stream);

            auto clippingRects = parseClippingRects(j);
            auto definitions = parseAnimationDefinitions(j);
            auto defaultAnimIndex = parseDefaultAnimIndex(j);

            validateDefaultFrameIndex(defaultAnimIndex, (unsigned int)clippingRects.size());
            validateDefinitions(definitions, (unsigned int)clippingRects.size(), defaultAnimIndex);

            auto resource = std::make_shared<CAnimation2DResource>();
            resource->m_animationFilePath = jsonPath;
            resource->m_animationSet.vecKeyFrameClipRects = std::move(clippingRects);
            resource->m_animationSet.mapAnimNameToAnimData = std::move(definitions);
            resource->m_animationSet.defaultAnimFrameIndex = defaultAnimIndex;

            return resource;
        }
        catch(const std::exception& e)
        {
            LOG_ERROR("Error occured when parsing animation data from JSON: " << e.what());
            return tl::make_unexpected(e.what());
        }
    }

} // namespace chestnut::engine
