// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#ifndef EIN_GEOMETRY_HPP
#define EIN_GEOMETRY_HPP

#include <GL.hpp>
#include <types.hpp>
#include <vector>

namespace Rendering
{
    namespace Resources
    {
        //TODO: figure out how to do this cache local in FUTURE
        //TODO: figure out how to minimize VAO switching cuz it's costly
        class Geometry
        {
            GLuint vao_id = 0, vbo_id = 0;

            GLuint count = 0;
        public:

            using pointer = std::shared_ptr<Geometry>;

            explicit Geometry(const std::vector<Ein::Vertex>& vertices) noexcept;

            GLuint vao() const noexcept
            {
                return vao_id;
            }

            //TODO: do i need this?
            GLuint vbo() const noexcept
            {
                return vbo_id;
            }

            GLuint vertex_count() const noexcept
            {
                return count;
            }

            ~Geometry();
        };
    }
}
#endif //EIN_GEOMETRY_HPP
