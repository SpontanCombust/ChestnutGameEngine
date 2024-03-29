#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/physics/collider_attributes.hpp"
#include "chestnut/engine/maths/vector2.hpp"

namespace chestnut::engine
{
    // A helper struct to relay information about collision and how it should affect two objects that were tested
    struct SCollisionResolutionData
    {
        bool isCollision;
        vec2f obj1Displacement;
        vec2f obj2Displacement;
    };

    class CHESTNUT_API CCollider2D
    {
    protected:
        EColliderActivity m_activity;
        CFlags<ECollisionPolicy> m_policyFlags;

        vec2f m_position;
        vec2f m_scale;

    public:
        CCollider2D();
        virtual ~CCollider2D() = default;


        EColliderActivity getActivity() const;
        void setActivity( EColliderActivity activity );
        
        CFlags<ECollisionPolicy> getPolicyFlags() const;
        void setPolicyFlags( CFlags<ECollisionPolicy> policyFlags );

        vec2f getPosition() const;
        void setPosition( vec2f position );

        vec2f getScale() const;
        void setScale( vec2f scale );


        virtual SCollisionResolutionData isColliding(const CCollider2D& other) const;
        SCollisionResolutionData resolveCollision(CCollider2D& other);
    };



    class CHESTNUT_API CPointCollider2D : public CCollider2D
    {
    public:
        virtual ~CPointCollider2D() = default;

        SCollisionResolutionData isColliding(const CCollider2D& other) const override;
    };

    class CHESTNUT_API CBoxCollider2D : public CCollider2D
    {
    private:
        vec2f m_size;

    public:
        CBoxCollider2D();
        ~CBoxCollider2D() = default;

        vec2f getSize() const;
        void setSize( vec2f size );

        // takes into account the scale
        vec2f getRealSize() const;

        SCollisionResolutionData isColliding(const CCollider2D& other) const override;
    };

    class CHESTNUT_API CCircleCollider2D : public CCollider2D
    {
    private:
        float m_radius;

    public:
        CCircleCollider2D();
        ~CCircleCollider2D() = default;

        float getRadius() const;
        void setRadius( float radius );

        // takes into account the scale
        vec2f getRealRadius() const;
        // takes into account the scale and gives the longest radius of the elipse
        float getMaxRealRadius() const;

        SCollisionResolutionData isColliding(const CCollider2D& other) const override;
    };

} // namespace chestnut::engine

