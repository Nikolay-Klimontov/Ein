// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#include <logger.hpp>
#include "geometry.hpp"

using namespace Rendering::Resources;

Geometry::Geometry(const std::vector<Ein::Vertex>& vertices) noexcept
{
    glGenVertexArrays(1, &vao_id);
    glGenBuffers(1, &vbo_id);

    //API restriction :(
    count = static_cast<GLuint>(vertices.size());

    LOG_INFO()<< "Vertex attribute object [uid = " << vao_id <<"] was created"<<std::endl;
    LOG_INFO()<< "Vertex buffer object [uid = " << vbo_id <<"] was created"<<std::endl;
    glBindVertexArray(vao_id);
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(Ein::Vertex)*count, vertices.data(), GL_STATIC_DRAW);
            //layout:    0      1       2
            //       [coords][normal][tex_coords]
            // Using interleaved data pattern as more universal
            glVertexAttribPointer(0, sizeof(Ein::Vertex::coord)/sizeof(float),     GL_FLOAT, GL_FALSE, sizeof(Ein::Vertex), (void*)offsetof(Ein::Vertex, coord));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, sizeof(Ein::Vertex::normal)/sizeof(float),    GL_FLOAT, GL_FALSE, sizeof(Ein::Vertex), (void*)offsetof(Ein::Vertex, normal));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, sizeof(Ein::Vertex::tex_coord)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Ein::Vertex), (void*)offsetof(Ein::Vertex, tex_coord));
            glEnableVertexAttribArray(2);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

Geometry::~Geometry()
{
    glDeleteBuffers(1, &vbo_id);
    LOG_INFO()<< "Vertex buffer object [uid = " << vbo_id <<"] was marked to delete"<<std::endl;
    glDeleteVertexArrays(1, &vao_id);
    LOG_INFO()<< "Vertex attribute object [uid = " << vao_id <<"] was marked to delete"<<std::endl;

}
