#include <type_traits>

namespace chestnut
{    
    template<typename SystemType, typename ...Args>
    void CEngine::attachMasterSystem( Args&&... args ) 
    {
        static_assert( std::is_base_of_v< ISystem, SystemType >, "SystemType must derive from ISystem!" );

        if( m_masterSystem )
        {
            delete m_masterSystem;
        }

        SystemType *system = new SystemType( *this, std::forward<Args>(args)... );

        m_masterSystem = system;
    }

    template< typename SystemType, typename ...Args >
    void CEngine::attachLogicSystem( systempriority_t priority, Args&&... args ) 
    {
        static_assert( std::is_base_of_v< ISystem, SystemType >, "SystemType must derive from ISystem!" );

        if( !hasSystem<SystemType>() )
        {
            SystemType *system = new SystemType( *this, std::forward<Args>(args)... );

            // search for the spot where to insert the system
            auto it = m_listLogicSystemNodes.begin();
            for( ;it != m_listLogicSystemNodes.end(); ++it )
            {
                if( it->priority > priority )
                {
                    break;
                }
            }

            SLogicSystemNode node { system, priority };

            m_listLogicSystemNodes.insert( it, node );
        }
    }

    template<typename SystemType, typename ...Args>
    void CEngine::attachRenderingSystem( systempriority_t priority, Args&&... args ) 
    {
        static_assert( std::is_base_of_v< IRenderingSystem, SystemType >, "SystemType must derive from IRenderingSystem!" );

        if( !hasSystem<SystemType>() )
        {
            SystemType *system = new SystemType( *this, std::forward<Args>(args)... );

            // search for the spot where to insert the system
            auto it = m_listRenderingSystemNodes.begin();
            for( ;it != m_listRenderingSystemNodes.end(); ++it )
            {
                if( it->priority > priority )
                {
                    break;
                }
            }

            SRenderingSystemNode node { system, priority };

            m_listRenderingSystemNodes.insert( it, node );
        }
    }

    template< typename SystemType >
    bool CEngine::hasSystem() const
    {
        if constexpr( std::is_base_of_v< IRenderingSystem, SystemType > )
        {
            for( const SRenderingSystemNode& node : m_listRenderingSystemNodes )
            {
                if( dynamic_cast< const SystemType * >( node.system ) != nullptr )
                {
                    return true;
                }
            }
        }
        else if constexpr( std::is_base_of_v< ISystem, SystemType > )
        {
            for( const SLogicSystemNode& node : m_listLogicSystemNodes )
            {
                if( dynamic_cast< const SystemType * >( node.system ) != nullptr )
                {
                    return true;
                }
            }

            if( dynamic_cast< const SystemType * >( m_masterSystem ) != nullptr )
            {
                return true;
            }
        }

        return false;
    }

    template< typename SystemType >
    SystemType* CEngine::getSystem() const
    {
        SystemType *foundSystem;

        if constexpr( std::is_base_of_v< IRenderingSystem, SystemType > )
        {
            for( const SRenderingSystemNode& node : m_listRenderingSystemNodes )
            {
                if( ( foundSystem = dynamic_cast< SystemType * >( node.system ) ) != nullptr )
                {
                    return foundSystem;
                }
            }
        }
        else if constexpr( std::is_base_of_v< ISystem, SystemType > )
        {
            for( const SLogicSystemNode& node : m_listLogicSystemNodes )
            {
                if( ( foundSystem = dynamic_cast< SystemType * >( node.system ) ) != nullptr )
                {
                    return foundSystem;
                }
            }
            
            if( ( foundSystem = dynamic_cast< SystemType * >( m_masterSystem ) ) != nullptr )
            {
                return foundSystem;
            }
        }

        return nullptr;
    }

    template< typename SystemType >
    systempriority_t CEngine::getSystemPriority() const
    {
        if constexpr( std::is_base_of_v< IRenderingSystem, SystemType > )
        {
            for( const SRenderingSystemNode& node : m_listRenderingSystemNodes )
            {
                if( ( dynamic_cast< SystemType * >( node.system ) ) != nullptr )
                {
                    return node.priority;
                }
            }
        }
        else if constexpr( std::is_base_of_v< ISystem, SystemType > )
        {
            for( const SLogicSystemNode& node : m_listLogicSystemNodes )
            {
                if( ( dynamic_cast< SystemType * >( node.system ) ) != nullptr )
                {
                    return node.priority;
                }
            }
            
            if( ( dynamic_cast< SystemType * >( m_masterSystem ) ) != nullptr )
            {
                return SYSTEM_PRIORITY_HIGHEST;
            }
        }

        return SYSTEM_PRIORITY_INVALID;
    }

    template< typename SystemType >
    void CEngine::detachSystem() 
    {
        if constexpr( std::is_base_of_v< IRenderingSystem, SystemType > )
        {
            for( auto it = m_listRenderingSystemNodes.begin(); it != m_listRenderingSystemNodes.end(); ++it )
            {
                if( dynamic_cast< SystemType * >( it->system ) != nullptr )
                {
                    delete it->system;
                    m_listRenderingSystemNodes.erase( it );
                    return;
                }
            }
        }
        else if constexpr( std::is_base_of_v< ISystem, SystemType > )
        {
            for( auto it = m_listLogicSystemNodes.begin(); it != m_listLogicSystemNodes.end(); ++it )
            {
                if( dynamic_cast< SystemType * >( it->system ) != nullptr )
                {
                    delete it->system;
                    m_listLogicSystemNodes.erase( it );
                    return;
                }
            }
            
            if( dynamic_cast< SystemType * >( m_masterSystem ) != nullptr )
            {
                delete m_masterSystem;
                m_masterSystem = nullptr;
            }
        }
    }

} // namespace chestnut