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

/**
 * @brief The shader wrapper.
 */
class Shader {
public:
    /**
     * @brief Create a new Shader instance which wraps the raw shader.
     *
     * This function creates a new Shader instance which wraps the raw
     * shader object. The returned instance does NOT delete the shader
     * object when it is deleted, so you should explicitly delete the
     * object.
     *
     * @param[in] shader  The shader object of OpenGL.
     * @returns The Shader instance.
     */
    static Shader FromRawShader(GLuint shader);

    /**
     * @brief Create a new Shader instance from the source file.
     *
     * This function creates a new Shader instance, and load the source
     * file in it.
     *
     * @warning This function does NOT compile the shader, so you should
                explicitly compile using `Shader::Compile` function.
     * @returns The Shader instance.
     */
    static Shader FromFile(GLenum shaderType, const char* const filename);

    /**
     * @brief The default constructor.
     */
    Shader();

    /**
     * @brief The copy constructor.
     */
    Shader(const Shader &obj);

    /**
     * @brief The destructor.
     */
    ~Shader();

    /**
     * @brief The copy assignment operator.
     */
    Shader &operator=(const Shader &obj);

    /**
     * @brief Swap the object.
     * @param[in,out] rhs  The Shader instance which is to be swapped with
     *                     this object.
     */
    void Swap(Shader &rhs);

    /**
     * @brief Get the raw shader object.
     * @return The shader object.
     */
    GLuint Get() const;

    /**
     * @brief Load the source of the shader.
     *
     * This function wraps glShaderSouce function.
     *
     * @param[in] count  The number of elements in the string and length
     *                   arrays.
     * @param[in] string  An array of pointers to strings containing the
     *                    source code to be loaded into the shader.
     * @param[in] size  An array of string lengths, or nullptr.
     *
     * @note If `size` is nullptr, each elements of the `string` is
     *       assumed to be null terminated.
     */
    Shader &Source(
        const size_t count,
        const char* const string[],
        const int size[] = nullptr);

    /**
     * @brief Load the source of the shader.
     *
     * You can use this overload function if you don't need to load
     * multiple source strings at a time.
     * 
     * @param[in] string  The source code string.
     * @param[in] size  The string length. If less than zero, `string` is
     *                  assumed to be null-terminated.
     */
    Shader &Source(const char* const string, const int size = -1)
    {
        const int sizeArray[]{ size };
        return Source(1, &string, sizeArray);
    }

    /**
     * @brief Load the source of the shader from a file.
     *
     * @param[in] filename  The file name of the source file.
     */
    Shader &SourceFromFile(const char* const filename);

    /**
     * @brief Compile the shader.
     */
    Shader &Compile();

private:
    std::unique_ptr<internal::IShaderHolder> m_holder; /**< The shader holder. */

    /**
     * @brief The constructor.
     *
     * @param[in] holder  The shader holder.
     */
    Shader(std::unique_ptr<internal::IShaderHolder> &&holder);
};

/**
 * @brief The exception thrown when the shader compilation is failed.
 */
class ShaderCompileException : public std::exception {
public:
    /**
     * @brief The constructor.
     * @param[in] message  The error message.
     */
    explicit ShaderCompileException(const char* const message):
        std::exception(),
        m_message(message)
    {}

    /**
     * @brief Return the error message.
     * @return The error message.
     */
    const char* what() const
    {
        return m_message.c_str();
    }

private:
    std::string m_message; /**< The error message. */
};

}} // kal::gl

#endif//OPENGL_COMMON_SHADER_HPP
