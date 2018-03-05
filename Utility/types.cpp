// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------

#include "types.hpp"
#include <stb_image.h>

namespace Ein
{

    Image2D::Image2D(const std::string& path) noexcept
    {
        int tmp_channels = 0;
        int tmp_width = 0, tmp_height = 0;
        m_data = stbi_load(path.c_str(), &tmp_width, &tmp_height, &tmp_channels, 0);

        m_width = static_cast<GLuint>(tmp_width);
        m_height = static_cast<GLuint>(tmp_height);

        switch (tmp_channels)
        {
            case 1:
                m_color_format = GL_RED;
                break;
            case 2:
                m_color_format = GL_RG;
                break;
            case 3:
                m_color_format = GL_RGB;
                break;
            case 4:
                m_color_format = GL_RGBA;
                break;

            default:
                stbi_image_free(m_data);

                m_data   = nullptr;
                m_width  = 0;
                m_height = 0;

                m_color_format = GL_FALSE;
        }
    }

    Image2D::~Image2D()
    {
        if(m_data)
        {
            stbi_image_free(m_data);
        }
    }
}
