#ifndef OPENGL_COMMON_SHADER_HOLDERS_HPP
#define OPENGL_COMMON_SHADER_HOLDERS_HPP

#include "opengl-common/shader.hpp"

#ifdef Apple
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace kal {
namespace gl {
namespace internal {

class IShaderHolder {
public:
    virtual ~IShaderHolder() {}

    virtual IShaderHolder* Clone() const = 0;
    virtual GLuint Get() const = 0;
};

class ManagedShaderHolder: public IShaderHolder {
public:
    ManagedShaderHolder(GLenum shaderType);
    ManagedShaderHolder(const ManagedShaderHolder &obj);

    ManagedShaderHolder &operator=(const ManagedShaderHolder &obj);

    ~ManagedShaderHolder();

    virtual ManagedShaderHolder* Clone() const;
    virtual GLuint Get() const;

private:
    const GLuint m_shader;
    int* const m_refCount;
};

class RawShaderHolder: public IShaderHolder {
public:
    explicit RawShaderHolder(GLuint shader);

    virtual RawShaderHolder* Clone() const;
    virtual GLuint Get() const;

private:
    const GLuint m_shader;
};

}}} // kal::gl::internal

#endif//OPENGL_COMMON_SHADER_HOLDERS_HPP
