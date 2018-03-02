// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "camera.hpp"

Camera::Camera(const glm::dvec3& position, const glm::dvec3& center, const glm::mat4& projection) noexcept
{
    pos = position;
    front = glm::normalize(center - position);

    pitch = glm::degrees(asin(front.y));
    yaw   = glm::degrees(acos(front.x * cos(asin(front.y))));

    proj = projection;
}

void Camera::move(Direction direction, double dt) noexcept
{

    switch (direction)
    {
        case Direction::forward:
            pos += front * velocity * dt;
            break;
        case Direction::backward:
            pos -= front * velocity * dt;
            break;
        case Direction::left:
            pos -= glm::normalize(glm::cross(front, up)) * velocity * dt;
            break;
        case Direction::right:
            pos += glm::normalize(glm::cross(front, up)) * velocity * dt;
            break;
        case Direction::up:
            pos += up * velocity * dt;
            break;
        case Direction::down:
            pos -= up * velocity * dt;
            break;
    }

}

void Camera::rotate(double yaw, double pitch) noexcept
{
    this->yaw += yaw;
    this->pitch = std::max(-89.0, std::min((this->pitch + pitch), 89.0));

    front = glm::normalize(glm::dvec3(cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
                                      sin(glm::radians(this->pitch)),
                                      sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))));
}

glm::mat4 Camera::view() const noexcept
{
    return glm::lookAt(pos, pos + front, up);
}

