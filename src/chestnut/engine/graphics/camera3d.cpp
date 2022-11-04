#include "chestnut/engine/graphics/camera3d.hpp"

#include <algorithm>


namespace chestnut::engine
{
    CCamera3D::CCamera3D()
    {
        m_worldUp = vec3f(0.0f, 1.0f, 0.0f);
        m_position = vec3f(0.0f, 0.0f, 0.0f);
        m_rotationDegrees = SEulerAngles{};
        m_fovDegrees = 70.0f;
        m_aspectRatio = 16.0f / 9.0f;

        m_up = vec3f(0.f, 1.f, 0.f);
        m_right = vec3f(1.f, 0.f, 0.f);
        m_direction = vec3f(0.f, 0.f, -1.f);

        m_viewMatrix = mat4f(1.f);
        m_projMatrix = mat4f(1.f);
    }

    void CCamera3D::setWorldUp(const vec3f& up)
    {
        m_worldUp = up;
    }

    const vec3f& CCamera3D::getWorldUp() const
    {
        return m_worldUp;
    }

    void CCamera3D::setPosition(const vec3f& position)
    {
        m_position = position;
    }

    const vec3f& CCamera3D::getPosition() const
    {
        return m_position;
    }

    void CCamera3D::setYaw(float yawDegrees)
    {
        m_rotationDegrees.yaw = yawDegrees;
    }

    void CCamera3D::setPitch(float pitchDegrees)
    {
        m_rotationDegrees.pitch = std::clamp(pitchDegrees, -89.f, 89.f);
    }

    // void CCamera3D::setRoll(float rollDegrees)
    // {
    //     m_rotation.roll = rollDegrees;
    // }

    void CCamera3D::setRotation(const SEulerAngles& angles)
    {
        m_rotationDegrees = angles;
        m_rotationDegrees.pitch = std::clamp(m_rotationDegrees.pitch, -89.f, 89.f);
    }

    const SEulerAngles& CCamera3D::getRotation() const
    {
        return m_rotationDegrees;
    }

    void CCamera3D::setFOV(float fovDegrees)
    {
        m_fovDegrees = std::clamp(fovDegrees, 0.1f, 179.9f);
    }

    float CCamera3D::getFOV() const
    {
        return m_fovDegrees;
    }

    void CCamera3D::setAspectRation(float aspect)
    {
        m_aspectRatio = aspect;
    }

    float CCamera3D::getAspectRatio() const
    {
        return m_aspectRatio;
    }






    void CCamera3D::calcViewFromLookAt(const vec3f& target)
    {
        lookAt(target);
        
        // calculate rotation based on up, rigth and direction vectors
        m_rotationDegrees.yaw = radiansToDegrees(std::atan2(m_direction.z, m_direction.x));
        m_rotationDegrees.pitch = radiansToDegrees(std::atan2(m_direction.y, std::sqrt(m_direction.x * m_direction.x + m_direction.z * m_direction.z)));
    }

    void CCamera3D::calcViewFromRotation()
    {
        float sinYaw = std::sin(degreesToRadians(m_rotationDegrees.yaw));
        float cosYaw = std::cos(degreesToRadians(m_rotationDegrees.yaw));
        float sinPitch = std::sin(degreesToRadians(m_rotationDegrees.pitch));
        float cosPitch = std::cos(degreesToRadians(m_rotationDegrees.pitch));

        vec3f direction = vec3f(cosYaw * cosPitch, sinPitch, sinYaw * cosPitch);
        lookAt(m_position + direction);
    }

    void CCamera3D::lookAt(const vec3f& target)
    {
        m_viewMatrix = matMakeLookAt(m_position, target, m_worldUp);
        
        m_right     = vec3f(m_viewMatrix(0,0), m_viewMatrix(0,1), m_viewMatrix(0,2));
        m_up        = vec3f(m_viewMatrix(1,0), m_viewMatrix(1,1), m_viewMatrix(1,2));
        m_direction = vec3f(-m_viewMatrix(2,0), -m_viewMatrix(2,1), -m_viewMatrix(2,2));
    }

    void CCamera3D::calcProjection()
    {
        m_projMatrix = matMakePerspective( degreesToRadians(m_fovDegrees), m_aspectRatio, 0.1f, 100.0f);
    }

    




    const vec3f& CCamera3D::getUp() const
    {
        return m_up;
    }

    const vec3f& CCamera3D::getRight() const
    {
        return m_right;
    }

    const vec3f& CCamera3D::getDirection() const
    {
        return m_direction;
    }

    const mat4f& CCamera3D::getViewMatrix() const
    {
        return m_viewMatrix;
    }

    const mat4f& CCamera3D::getProjectionMatrix() const
    {
        return m_projMatrix;
    }

} // namespace chestnut::engine
