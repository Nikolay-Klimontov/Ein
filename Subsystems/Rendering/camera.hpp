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
    glm::vec3 position;

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right ;

    float pitch_angle = 0.0f;
    float yaw_angle = 0.0f;

public:
    Camera(const glm::vec3& position, const glm::vec3& direction) noexcept;

    void move(glm::vec3 direction, float velocity, float dt) noexcept;

    void pitch(float angle) noexcept;
    void yaw(float angle) noexcept;

    glm::mat4 view() const noexcept;
};

#endif //EIN_CAMERA_HPP
