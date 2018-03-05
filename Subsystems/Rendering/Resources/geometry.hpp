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
        //! @brief Geometry buffer class
        class Geometry final
        {
            GLuint vao_id = 0, vbo_id = 0, ebo_id = 0;

            GLuint v_count = 0;
            GLuint i_count = 0;
        public:

            using pointer = std::shared_ptr<Geometry>;

            Geometry(const std::vector<Ein::Vertex>& vertices) noexcept;
            Geometry(const std::vector<Ein::Vertex>& vertices, const std::vector<GLuint>& indices) noexcept;

            GLuint vao() const noexcept
            {
                return vao_id;
            }

            bool indexed() const noexcept
            {
                return ebo_id != 0;
            }

            GLuint vertex_count() const noexcept
            {
                return v_count;
            }

            GLuint index_count() const noexcept
            {
                return i_count;
            }

            ~Geometry();
        private:

            void configure_layout() const noexcept;
        };
    }
}
#endif //EIN_GEOMETRY_HPP
