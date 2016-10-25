/**
 * @file   program.hpp
 * @author nullkal <nullkal@nil.nu>
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#ifndef OPENGL_COMMON_PROGRAM_HPP
#define OPENGL_COMMON_PROGRAM_HPP

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

class IProgramHolder;

} // kal::gl::internal

class Shader;

/**
 * @brief The program wrapper.
 */
class Program {
public:
    /**
     * @brief Create a new Program instance which wraps the raw program.
     *
     * This function creates a new Program instance which wraps the raw
     * program object. The returned instance does NOT delete the program
     * object when it is deleted, so you should explicitly delete the
     * object.
     *
     * @param[in] program  The program object of OpenGL.
     * @returns The Program instance.
     */
    static Program FromRawProgram(GLuint program);

    /**
     * @brief The default constructor.
     */
    Program();

    /**
     * @brief The copy constructor.
     */
    Program(const Program &obj);

    /**
     * @brief The destructor.
     */
    ~Program();

    /**
     * @brief The copy assignment operator.
     */
    Program &operator=(const Program &obj);

    /**
     * @brief The type conversion operator.
     */
    operator GLuint() const;

    /**
     * @brief Swap the object.
     * @param[in,out] rhs  The Program instance which is to be swapped with
     *                     this object.
     */
    void Swap(Program &rhs);

    /**
     * @brief Get the raw program object.
     * @return The program object.
     */
    GLuint Get() const;

    /**
     * @brief Use the program object.
     */
    void Use() const;

    /**
     * @brief Attach a Shader object to the program.
     *
     * @param[in] shader  The shader object.
     */
    Program &AttachShader(const Shader &shader);

    /**
     * @brief Link the program.
     */
    Program &Link();

private:
    std::unique_ptr<internal::IProgramHolder> m_holder; /**< The program holder. */

    /**
     * @brief The constructor.
     *
     * @param[in] holder  The program holder.
     */
    Program(std::unique_ptr<internal::IProgramHolder> &&holder);
};

/**
 * @brief The exception thrown when the linking of the program is failed.
 */
class ProgramLinkException : public std::exception {
public:
    /**
     * @brief The constructor.
     * @param[in] message  The error message.
     */
    explicit ProgramLinkException(const char* const message):
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

#endif//OPENGL_COMMON_PROGRAM_HPP
