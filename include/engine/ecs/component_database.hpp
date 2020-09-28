#ifndef __CHESTNUT_COMPONENT_DATABASE_H__
#define __CHESTNUT_COMPONENT_DATABASE_H__

#include "component.hpp"

#include <unordered_map>

namespace chestnut
{   //TODO class testing
    class CComponentDatabase
    {
    private:
        std::unordered_map< std::string, std::unordered_map< uint64_t, IComponent* > > m_componentMaps;

    public:
        bool hasComponentType( std::string compTypeStr ) const;
        bool hasComponent( std::string compTypeStr, uint64_t guid ) const;
        bool pushComponent( IComponent *component );
        IComponent *getComponent( std::string compTypeStr, uint64_t guid );
        IComponent *pullComponent( std::string compTypeStr, uint64_t guid );
        void eraseComponent( std::string compTypeStr, uint64_t guid );
        void clearComponents();

        template<typename T, typename std::enable_if< std::is_base_of< IComponent, T >::value >::type* = nullptr >
        bool fillComponentMapOfType( std::unordered_map< uint64_t, T* >& outCompMapRef, std::string compTypeStr ) const;
    };

} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_DATABASE_H__