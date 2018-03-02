// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------

#include "readers.hpp"
#include <stb_image.h>


namespace Utils
{
    std::string load_text(const std::string &path) noexcept
    {
        std::ifstream t(path);

        if (t.fail())
        {
            LOG_FAILED_TO_READ(path);
            return std::string();
        }

        std::string str;

        t.seekg(0, std::ios::end);
        str.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        str.assign((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());

        LOG_FILE_WAS_READ(path);
        return std::move(str);
    }

    Ein::Image load_image(const std::string &path) noexcept
    {
        Ein::Image img;


        stbi_set_flip_vertically_on_load(true);
        img.data = stbi_load(path.c_str(), &img.width, &img.height, &img.channels, 0);

        if (img.channels == 1)
            img.color_format = GL_RED;
        else if (img.channels == 3)
            img.color_format = GL_RGB;
        else if (img.channels == 4)
            img.color_format = GL_RGBA;

        return img;
    }

    void free_image(Ein::Image &img) noexcept
    {
        stbi_image_free(img.data);

        img.width = 0;
        img.height = 0;
        img.channels = 0;
        img.data = nullptr;
    }

}