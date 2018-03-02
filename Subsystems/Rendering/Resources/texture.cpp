// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------

#include "texture.hpp"

using namespace Rendering::Resources;

Texture::Texture(GLuint width, GLuint height, GLubyte* data, GLenum format) noexcept
{
    glGenTextures(1, &uid);
    glBindTexture(GL_TEXTURE_2D, uid);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // export pixel data to gpu
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
    glDeleteTextures(1, &uid);
}

Texture::Texture(const Ein::Image& image) noexcept:
    Texture(image.width, image.height, image.data, image.color_format)
{
}
