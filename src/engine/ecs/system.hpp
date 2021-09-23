#ifndef __CHESTNUT_SYSTEM_H__
#define __CHESTNUT_SYSTEM_H__

namespace chestnut
{
    class CEngine; // forward declaration
    
    class ISystem
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
    
} // namespace chestnut

#endif // __CHESTNUT_SYSTEM_H__