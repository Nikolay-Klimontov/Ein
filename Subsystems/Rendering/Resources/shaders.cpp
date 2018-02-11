// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#include <logger.hpp>
#include "shaders.hpp"

using namespace Rendering::Resources;

std::string to_string(GLenum shader_type)
{
    switch(shader_type)
    {
        case GL_VERTEX_SHADER:
            return __STR(GL_VERTEX_SHADER);
        case GL_FRAGMENT_SHADER:
            return __STR(GL_FRAGMENT_SHADER);
        case GL_GEOMETRY_SHADER:
            return __STR(GL_GEOMETRY_SHADER);
        default:
            return __STR(GL_UNKNOWN_SHADER_TYPE);
    }
}

Shader::Shader(const std::string& sources, GLenum type)
{
    auto compile = [](GLuint id, const char* source)->bool
    {
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        return success!=0;
    };

    auto get_info = [](GLuint id)->std::string
    {
        const size_t size = 1024;
        char log[size];
        glGetShaderInfoLog(id, size, nullptr, log);
        return std::string(log);
    };

    uid = glCreateShader(type);

    LOG_INFO()<< to_string(type) << " [uid = "<<uid <<"] was created"<< std::endl;

    if(!compile(uid, sources.c_str()))
    {
        LOG_CRITICAL()<< to_string(type) << " compilation failed:" << std::endl << get_info(uid) <<std::endl;
        mark_to_delete();
    }

    LOG_INFO()<< to_string(type) << " compiled [uid = "<<uid <<"]"<< std::endl;
}

Shader::~Shader()
{
    mark_to_delete();
}

void Shader::mark_to_delete() noexcept
{
    if(uid)
    {
        glDeleteShader(uid);
        LOG_INFO()<<"Shader [uid = "<<uid <<"] was marked to delete"<< std::endl;
        uid = 0;
    }
}

Shader_program::Shader_program(const std::vector<Shader_ptr>& shaders)
{
    if(shaders.empty())
    {
        LOG_ERROR()<<"No shaders to link"<< std::endl;
        return ;
    }
    uid = glCreateProgram();
    LOG_INFO()<< "Shader program [uid = "<<uid <<"] was created"<< std::endl;

    for(auto& shader: shaders)
    {
        glAttachShader(uid, shader->id());
    }

    glLinkProgram(uid);

    for(auto& shader: shaders)
    {
        glDetachShader(uid, shader->id());
    }

    int success;
    glGetShaderiv(uid, GL_LINK_STATUS, &success);

    if(!success)
    {
        const size_t size = 1024;
        char log[size];
        glGetProgramInfoLog(uid, size, nullptr, log);
        LOG_ERROR() << "Shader program [uid = "<<uid <<"] linkage failed:" << std::endl << log <<std::endl;
        mark_to_delete();
    }

}

Shader_program::~Shader_program()
{
    mark_to_delete();
}

void Shader_program::mark_to_delete() noexcept
{
    if(uid)
    {
        glDeleteProgram(uid);
        LOG_INFO() << "Shader program [uid = " << uid << "] was marked to delete" << std::endl;
        uid = 0;
    }
}
