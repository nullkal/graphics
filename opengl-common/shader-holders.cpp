#define GLEW_STATIC
#include <GL/glew.h>

#include "shader-holders.hpp"

#include <algorithm>

namespace kal {
namespace gl {
namespace internal {

ManagedShaderHolder::ManagedShaderHolder(GLenum shaderType):
    m_refCount(new int(1)),
    m_shader(glCreateShader(shaderType))
{
    // FIXME: throw an exception if this constructor fails to create a shader
}

ManagedShaderHolder::ManagedShaderHolder(const ManagedShaderHolder &obj):
    m_refCount(obj.m_refCount),
    m_shader(obj.m_shader)
{
    ++(*m_refCount);
}

ManagedShaderHolder &ManagedShaderHolder::operator=(const ManagedShaderHolder &obj)
{
    using namespace std;

    ManagedShaderHolder temp(obj);
    swap(*this, temp);

    return *this;
}

ManagedShaderHolder::~ManagedShaderHolder()
{
    --(*m_refCount);
    if (*m_refCount <= 0) {
        delete m_refCount;
        glDeleteShader(m_shader);
    }
}

ManagedShaderHolder* ManagedShaderHolder::Clone() const
{
    return new ManagedShaderHolder{ *this };
}

GLuint ManagedShaderHolder::Get() const
{
    return m_shader;
}

RawShaderHolder::RawShaderHolder(GLuint shader):
    m_shader(shader)
{}

RawShaderHolder* RawShaderHolder::Clone() const
{
    return new RawShaderHolder{ *this };
}

GLuint RawShaderHolder::Get() const
{
    return m_shader;
}

}}} // kal::gl