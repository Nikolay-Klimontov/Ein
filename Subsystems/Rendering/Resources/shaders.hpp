// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#ifndef EIN_SHADERS_HPP
#define EIN_SHADERS_HPP

#include <string>
#include <GL.hpp>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rendering
{
    namespace Resources
    {
        //Temporary object, MUST be deleted once all shader programs linked
        class Shader final
        {
            GLuint uid = 0;
        public:

            using pointer = std::shared_ptr<Shader>;

            explicit Shader(const std::string& sources, GLenum type);

            //! @returns 0 in case of an error during resource initialization, resource id otherwise
            GLuint id() const noexcept
            {
                return uid;
            };

            ~Shader();
        private:
            //! @brief OpenGL driver mark this resource for deletion
            void mark_to_delete() noexcept;
        };

        //TODO: figure out how to do this cache local in FUTURE
        class Shader_program final
        {
            GLuint uid = 0;


        public:

            //TODO: make this template
            struct Var
            {
                GLint loc;

            public:

                void operator= (GLint val) noexcept
                {
                    //assert(type == GL_FLOAT_VEC3);

                    glUniform1iv(loc, 1, &val);
                }

                void operator= (glm::vec3 val) noexcept
                {
                    //assert(type == GL_FLOAT_VEC3);

                    glUniform3fv(loc, 1, glm::value_ptr(val));
                }
                void operator= (glm::vec4 val) noexcept
                {
                    //assert(type == GL_FLOAT_VEC4);

                    glUniform4fv(loc, 1, glm::value_ptr(val));
                }
                void operator= (const glm::mat4& val) noexcept
                {
                    //assert(type == GL_FLOAT_MAT4);

                    glUniformMatrix4fv(loc,  1, GL_FALSE, glm::value_ptr(val));
                }
            };

            using pointer = std::shared_ptr<Shader_program>;

            explicit Shader_program(const std::vector<Shader::pointer>& shaders);

            //! @returns 0 in case of an error during resource initialization, resource id otherwise
            GLuint id() const noexcept
            {
                return uid;
            }

            Var variable(const std::string& name) noexcept
            {
                return {glGetUniformLocation(uid, name.c_str())};
            }

            ~Shader_program();

        private:
            //! @brief OpenGL driver mark this resource for deletion
            void mark_to_delete() noexcept;
        };

    }
}
#endif //EIN_SHADERS_HPP
