#ifndef __CHESTNUT_ENGINE_CAMERA3D_H__
#define __CHESTNUT_ENGINE_CAMERA3D_H__

#include "chestnut/engine/macros.hpp"
#include "../maths/matrix4.hpp"
#include "../maths/vector3.hpp"
#include "../maths/angles.hpp"


namespace chestnut::engine
{
    class CHESTNUT_API CCamera3D
    {
    private:
        vec3f m_worldUp;
        vec3f m_position;
        SEulerAngles m_rotationDegrees;
        float m_fovDegrees;
        float m_aspectRatio;

        vec3f m_up;
        vec3f m_right;
        vec3f m_direction;

        mat4f m_viewMatrix;
        mat4f m_projMatrix;


    public:
        CCamera3D();


        void setWorldUp(const vec3f& up);
        const vec3f& getWorldUp() const;

        void setPosition(const vec3f& position);
        const vec3f& getPosition() const;

        void setYaw(float yawDegrees);
        void setPitch(float pitchDegrees);
        // void setRoll(float rollDegrees);
        void setRotation(const SEulerAngles& angles);
        const SEulerAngles& getRotation() const;

        void setFOV(float fovDegrees);
        float getFOV() const;

        void setAspectRation(float aspect);
        float getAspectRatio() const;


        void calcViewFromLookAt(const vec3f& target);
        void calcViewFromRotation();
        void calcProjection();


        const vec3f& getUp() const;
        const vec3f& getRight() const;
        const vec3f& getDirection() const;

        const mat4f& getViewMatrix() const;
        const mat4f& getProjectionMatrix() const;

    private:
        void lookAt(const vec3f& target);
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_CAMERA3D_H__