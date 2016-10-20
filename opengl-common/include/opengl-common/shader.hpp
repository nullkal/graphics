/**
 * @file   shader.hpp
 * @author nullkal <nullkal@nil.nu>
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#ifndef OPENGL_COMMON_SHADER_HPP
#define OPENGL_COMMON_SHADER_HPP

#ifdef Apple
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <memory>
#include <string>

namespace kal {
namespace gl {
namespace internal {

class IShaderHolder;

} // kal::gl::internal

class Shader {
public:
    static Shader FromRawShader(GLuint shader);
    static Shader FromFile(GLenum shaderType, const char* const filename);

    Shader();
    Shader(const Shader &obj);

    ~Shader();

    Shader &operator=(const Shader &obj);

    void Swap(Shader &rhs);

    GLuint Get() const;

    Shader &Source(
        const size_t count,
        const char* const string[],
        const int size[] = nullptr);

    Shader &Source(const char* const string, const int size = -1)
    {
        const int sizeArray[]{ size };
        return Source(1, &string, sizeArray);
    }

    Shader &SourceFromFile(const char* const filename);

    Shader &Compile();

private:
    std::unique_ptr<internal::IShaderHolder> m_holder;

    Shader(std::unique_ptr<internal::IShaderHolder> &&holder);
};

class ShaderCompileException : public std::exception {
public:
    explicit ShaderCompileException(const char* const message):
        std::exception(),
        m_message(message)
    {}

    const char* what() const
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

}} // kal::gl

#endif//OPENGL_COMMON_SHADER_HPP
