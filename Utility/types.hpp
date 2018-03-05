// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#ifndef EIN_TYPES_HPP
#define EIN_TYPES_HPP

#include <string>
#include <memory>
#include <vector>

#include <GL.hpp>
#include <glm/glm.hpp>

namespace Ein
{
    using vec2 = glm::vec2;
    using vec3 = glm::vec3;
    using vec4 = glm::vec4;

    struct Vertex
    {
        vec3 coord;    // position in 3D space
        vec3 normal;   // normal of this vertex
        vec2 tex_coord;// texture coordinates of this vertex
    };//8floats * 4bytes = 32bytes per vertex. All aligned on 32bit border,
      //so there no holes in memory, i hope (^_^)

    //! @brief Temporary class for image/texture data management
    //! @warning Delete this after
    class Image2D
    {
        GLuint m_width = 0, m_height = 0;
        GLenum m_color_format = GL_RGB;
        unsigned char* m_data = nullptr;

    public:

        Image2D(const Image2D&) = delete;
        Image2D& operator=(const Image2D&) = delete;

        using pointer = std::shared_ptr<Image2D>;

        explicit Image2D(const std::string& path) noexcept;

        GLuint height() const noexcept
        {
            return m_height;
        }

        GLuint width() const noexcept
        {
            return m_width;
        }

        GLenum color_format() const noexcept
        {
            return m_color_format;
        }

        GLubyte * data() const noexcept
        {
            return m_data;
        }

        ~Image2D();
    };

}

#endif //EIN_TYPES_HPP
