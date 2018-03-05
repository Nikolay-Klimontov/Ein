// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------

#ifndef EIN_TEXTURE_HPP
#define EIN_TEXTURE_HPP

#include <GL.hpp>
#include <string>
#include <memory>
#include <types.hpp>
#include <templates.hpp>

namespace Rendering
{
    namespace Resources
    {
        class Texture final
        {
            std::string name;
            GLuint uid;

        public:

            using pointer = std::shared_ptr<Texture>;

            Texture(const std::string& name, Ein::Image2D::pointer image) noexcept;
            explicit Texture(const std::string& name, GLuint width, GLuint height, GLubyte *data, GLenum format) noexcept;

            GLuint id() const noexcept
            {
                return uid;
            }

            ~Texture();

        };
    }
}

#endif //EIN_TEXTURE_HPP
