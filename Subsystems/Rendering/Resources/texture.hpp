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
#include <types.hpp>
#include <templates.hpp>

namespace Rendering
{
    namespace Resources
    {
        class Texture final
        {
            GLuint uid;

        public:

            using pointer = std::shared_ptr<Texture>;

            Texture(GLuint width, GLuint heigth, GLubyte *data, GLenum format) noexcept;

            Texture(const Ein::Image &image) noexcept;

            GLuint id() const noexcept
            {
                return uid;
            }

            ~Texture();

        };
    }
}

#endif //EIN_TEXTURE_HPP
