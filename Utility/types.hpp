// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#ifndef EIN_TYPES_HPP
#define EIN_TYPES_HPP

#include <glm/glm.hpp>
#include <GL.hpp>
#include <vector>

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

    //TODO: rewrite this shit
    struct Image
    {
        GLenum color_format = GL_RGB;
        GLint  channels     = 0;
        GLint width         = 0;
        GLint height        = 0;

        unsigned char* data = nullptr;
    };
}

#endif //EIN_TYPES_HPP
