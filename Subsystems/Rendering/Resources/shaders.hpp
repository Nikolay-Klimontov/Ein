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

namespace Rendering
{
    namespace Resources
    {
        //Temporary object, MUST be deleted once all shader programs linked
        class Shader final
        {
            GLuint uid = 0;
        public:

            PREVENT_COPY(Shader)

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

        using Shader_ptr = std::shared_ptr<Shader>;

        //TODO: figure out how to do this cache local in FUTURE
        class Shader_program final
        {
            GLuint uid = 0;

        public:
            PREVENT_COPY(Shader_program)

            explicit Shader_program(const std::vector<Shader_ptr>& shaders);

            //! @returns 0 in case of an error during resource initialization, resource id otherwise
            GLuint id() const noexcept
            {
                return uid;
            }

            ~Shader_program();

        private:
            //! @brief OpenGL driver mark this resource for deletion
            void mark_to_delete() noexcept;
        };

        //TODO: figure out how to make this
        struct Variable
        {
            GLchar* name;
            GLint location;
            GLenum type;
        };

    }
}
#endif //EIN_SHADERS_HPP
