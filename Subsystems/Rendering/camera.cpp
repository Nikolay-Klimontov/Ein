// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& direction) noexcept
{

}


void Camera::move(glm::vec3 direction, float velocity, float dt) noexcept
{
    direction.x = direction.x * cosf(yaw_angle) * cosf(pitch_angle);
    direction.z = direction.z * sinf(yaw_angle) * cosf(pitch_angle);
    direction.y = direction.y * sinf(pitch_angle);

    position += direction*velocity*dt;
}

void Camera::pitch(float angle) noexcept
{
    pitch_angle +=angle;

    pitch_angle = std::min(89.0f, std::max(-89.0f, pitch_angle));
}

void Camera::yaw(float angle) noexcept
{
    yaw_angle += angle;
}

glm::mat4 Camera::view() const noexcept
{
    return glm::mat4();
}
