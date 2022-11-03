#ifndef __CHESTNUT_ENGINE_SYSTEM_H__
#define __CHESTNUT_ENGINE_SYSTEM_H__

#include "chestnut/engine/macros.hpp"


namespace chestnut::engine
{
    class CEngine; // forward declaration
    
    class CHESTNUT_API ISystem
    {
    private:
        CEngine& m_engine;

    protected:
        CEngine& getEngine() const;

    public:
        ISystem( CEngine& engine );
        virtual ~ISystem() = default;

        virtual void update( float deltaTime ) = 0;
    };
    
} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_SYSTEM_H__