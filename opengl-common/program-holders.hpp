/**
 * @file   program-holders.hpp
 * @author nullkal <nullkal@nil.nu>
 *
 * @brief  declares IProgramHolder, ManagedProgramHolder, and
 *         RawProgramHolder.
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#ifndef OPENGL_COMMON_PROGRAM_HOLDERS_HPP
#define OPENGL_COMMON_PROGRAM_HOLDERS_HPP

#ifdef Apple
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace kal {
namespace gl {
namespace internal {

/**
 * @brief The interface of program holder.
 */
class IProgramHolder {
public:
    /**
     * @brief The destructor.
     */
    virtual ~IProgramHolder() {}

    /**
     * @brief Clone the instance.
     *
     * @note The pointer this function returns should be deletable using
     *       `delete` operator.
     *
     * @return The cloned IProgramHolder object.
     */
    virtual IProgramHolder* Clone() const = 0;

    /**
     * @brief  Get the holding program object.
     * @return The program object.
     */
    virtual GLuint Get() const = 0;
};

/**
 * @brief The program holder which manages all the life cycle.
 *
 * This program holder automatically creates a program object in the
 * constructor, and deletes it when the last object referencing it is
 * deleted.
 */
class ManagedProgramHolder : public IProgramHolder {
public:
    /**
     * @brief The default constructor.
     */
    ManagedProgramHolder();

    /**
     * @brief The copy constructor.
     */
    ManagedProgramHolder(const ManagedProgramHolder &obj);

    /**
     * @brief The copy assignment operator.
     */
    ManagedProgramHolder &operator=(const ManagedProgramHolder &obj);

    /**
     * @brief The destructor.
     */
    ~ManagedProgramHolder();

    virtual ManagedProgramHolder* Clone() const;
    virtual GLuint Get() const;

private:
    int* const m_refCount; /**< The referece counter.  */
    const GLuint m_program; /**< The holding program object. */
};

/**
 * @brief The program holder which only holds the program object ID.
 *
 * This program holder doesn't create/delete the program object. When you
 * use this class's instance, you must manage manually the life cycle of
 * the program object (i.e. you must call `glCreateProgram` before using
 * the object, and call `glDeleteProgram` after using it).
 */
class RawProgramHolder : public IProgramHolder {
public:
    /**
     * @brief The constructor.
     *
     * @param[in] program  The program object.
     */
    explicit RawProgramHolder(GLuint program);

    virtual RawProgramHolder* Clone() const;
    virtual GLuint Get() const;

private:
    const GLuint m_program; /**< The holding program object. */
};

}}} // kal::gl::internal

#endif//OPENGL_COMMON_PROGRAM_HOLDERS_HPP
