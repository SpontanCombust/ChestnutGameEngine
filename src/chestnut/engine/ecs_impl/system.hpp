#pragma once


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

