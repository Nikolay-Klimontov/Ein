// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------

#ifndef EIN_CAMERA_HPP
#define EIN_CAMERA_HPP

#include <glm/glm.hpp>

class Camera
{
    glm::dvec3 pos   = glm::dvec3(0.0, 0.0,  0.0);
    glm::dvec3 front = glm::dvec3(0.0, 0.0, -1.0);
    glm::dvec3 up    = glm::dvec3(0.0, 1.0,  0.0);

    double pitch = 0.0, yaw = 0.0;

    const double velocity = 1.0;

    glm::mat4 proj;

public:

    //TODO: a bit mask or a normalized vector instead of this
    enum class Direction{forward, backward, left, right, up, down};

    Camera(const glm::dvec3& position, const glm::dvec3& direction, const glm::mat4& projection) noexcept;

    void move(Direction direction, double dt) noexcept;
    void rotate(double yaw, double pitch) noexcept;

    glm::vec3 position() const noexcept
    {
        return  glm::vec3(pos.x, pos.y, pos.z);
    }

    glm::mat4 view() const noexcept;

    glm::mat4 projection() const noexcept
    {
        return proj;
    };
};

#endif //EIN_CAMERA_HPP
