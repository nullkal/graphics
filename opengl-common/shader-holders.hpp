/**
 * @file   shader-holders.hpp
 * @author nullkal <nullkal@nil.nu>
 *
 * @brief  declares IShaderHolder, ManagedShaderHolder, and
 *         RawShaderHolder.
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#ifndef OPENGL_COMMON_SHADER_HOLDERS_HPP
#define OPENGL_COMMON_SHADER_HOLDERS_HPP

#ifdef Apple
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace kal {
namespace gl {
namespace internal {

/**
 * @brief The interface of shader holder.
 */
class IShaderHolder {
public:
    /**
     * @brief The destructor
     */
    virtual ~IShaderHolder() {}

    /**
     * @brief Clone the instance
     *
     * @note The pointer this function returns should be deletable using
     *       `delete` operator.
     *
     * @return The cloned IShaderHolder instance
     */
    virtual IShaderHolder* Clone() const = 0;

    /**
     * @brief  Get the holding shader object
     * @return The shader object
     */
    virtual GLuint Get() const = 0;
};

/**
* @brief The shader holder which manages all the life cycle.
*
* This shader holder automatically creates a shader object in the
* constructor, and deletes it when the last object referencing it is
* deleted.
*/
class ManagedShaderHolder: public IShaderHolder {
public:
    /**
     * @brief The constructor
     *
     * @param[in] shaderType  The shader type you want
     */
    ManagedShaderHolder(GLenum shaderType);

    /**
     * @brief The copy constructor
     */
    ManagedShaderHolder(const ManagedShaderHolder &obj);

    /**
     * @brief The copy assignment operator
     */
    ManagedShaderHolder &operator=(const ManagedShaderHolder &obj);

    /**
     * @brief The destructor
     */
    ~ManagedShaderHolder();

    virtual ManagedShaderHolder* Clone() const;
    virtual GLuint Get() const;

private:
    int* const m_refCount; /**< The referece counter */
    const GLuint m_shader; /**< The holding shader object */
};

/**
 * @brief The shader holder which only holds the shader object ID.
 *
 * This shader holder doesn't create/delete the shader object. When you use
 * this class's instance, you must manage manually the life cycle of the
 * shader object (i.e. you must call `glCreateShader` before using the
 * object, and call `glDeleteShader` after using it).
 */
class RawShaderHolder: public IShaderHolder {
public:
    /**
     * @brief The constructor
     *
     * @param[in] shader  The shader object
     */
    explicit RawShaderHolder(GLuint shader);

    virtual RawShaderHolder* Clone() const;
    virtual GLuint Get() const;

private:
    const GLuint m_shader; /**< The holding shader object */
};

}}} // kal::gl::internal

#endif//OPENGL_COMMON_SHADER_HOLDERS_HPP
