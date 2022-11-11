#include <type_traits>

namespace chestnut::engine
{    
    template<typename SystemType>
    SystemType* CEngine::getLogicSystem() const
    {
        static_assert(std::is_base_of_v< ILogicSystem, SystemType >, "Given SystemType is not a LogicSystem");

        for( ILogicSystem *sys : m_listLogicSystems )
        {
            SystemType *foundSystem;
            if( ( foundSystem = dynamic_cast<SystemType *>(sys) ) != nullptr )
            {
                return foundSystem;
            }
        }

        return nullptr;
    }

    template<typename SystemType>
    SystemType* CEngine::getRenderingSystem() const
    {
        static_assert(std::is_base_of_v< IRenderingSystem, SystemType >, "Given SystemType is not a RenderingSystem");

        for( IRenderingSystem *sys : m_listRenderingSystems )
        {
            SystemType *foundSystem;
            if( ( foundSystem = dynamic_cast<SystemType *>(sys) ) != nullptr )
            {
                return foundSystem;
            }
        }

        return nullptr;
    }

} // namespace chestnut::engine
