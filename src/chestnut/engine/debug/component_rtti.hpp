#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/debug/ecs_lifetime/component_factory.hpp"
#include "chestnut/engine/debug/ecs_lifetime/component_serializer_provider.hpp"
#include "chestnut/engine/debug/editor/component_views/i_gui_component_view.hpp"
		
#include <typeindex>
#include <unordered_map>

namespace chestnut::engine::debug
{
    struct SComponentRTTI
    {
        const char *name;
        ComponentFactoryCreateCallback factoryCreate;
        ComponentFactoryDisposeCallback factoryDispose;
        ComponentSerializerCallback serializer;
        ComponentDeserializerCallback deserializer;
        IGuiComponentView *guiView;
    };

    
    CHESTNUT_API const std::unordered_map<std::type_index, SComponentRTTI>& getComponentRTTIRegistry();

    CHESTNUT_API void registerComponentRTTI(std::type_index typeIndex, SComponentRTTI&& traits);

    // For this automated registration to work you have to beforehand include headers
    // with serializer functions (to_json and from_json) and component-to-guiview mappings
    template<class C>
    void registerComponentRTTI();

    // Return null on error
    CHESTNUT_API SComponentRTTI* getComponentRTTIByTypeIndex(std::type_index typeIndex);
    // Return null on error
    CHESTNUT_API SComponentRTTI* getComponentRTTIByTypeName(const char *typeName);

} // namespace chestnut::engine::debug

#include "component_rtti.inl"
