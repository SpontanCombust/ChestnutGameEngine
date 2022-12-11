#include "chestnut/engine/misc/rtti_type_name.hpp"
#include "chestnut/engine/debug/log.hpp"

#include <type_traits>

namespace chestnut::engine::debug
{
    template<class C>
    void registerComponentRTTI()
    {
        std::type_index typeIndex = typeid(C);
        const char *typeName = rttiTypeName(typeIndex);
        IGuiComponentView *guiView = nullptr;

        using GuiViewType = typename CComponentToGuiViewMapping<C>::Mapping;
        if constexpr(!std::is_same_v<GuiViewType, nullptr_t>)
        {
            guiView = new GuiViewType();
        }
        else
        {
            LOG_WARNING("CComponentToGuiViewMapping template specialization not provided for a registered type " << typeName <<
                        ". Make sure you've included its header file beforehand.");
            CLogger::flush();
        }

        registerComponentRTTI(typeIndex, {
            typeName,
            CComponentFactory<C>::create,
            CComponentFactory<C>::dispose,
            CComponentSerializerProvider<C>::serialize,
            CComponentSerializerProvider<C>::deserialize,
            guiView
        });
    }

} // namespace chestnut::engine::debug
