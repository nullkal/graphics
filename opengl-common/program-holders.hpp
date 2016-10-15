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

class IProgramHolder {
public:
    virtual ~IProgramHolder() {}

    virtual IProgramHolder* Clone() const = 0;
    virtual GLuint Get() const = 0;
};

class ManagedProgramHolder : public IProgramHolder {
public:
    ManagedProgramHolder();
    ManagedProgramHolder(const ManagedProgramHolder &obj);

    ManagedProgramHolder &operator=(const ManagedProgramHolder &obj);

    ~ManagedProgramHolder();

    virtual ManagedProgramHolder* Clone() const;
    virtual GLuint Get() const;

private:
    int* const m_refCount;
    const GLuint m_program;
};

class RawProgramHolder : public IProgramHolder {
public:
    explicit RawProgramHolder(GLuint program);

    virtual RawProgramHolder* Clone() const;
    virtual GLuint Get() const;

private:
    const GLuint m_program;
};

}}} // kal::gl::internal

#endif//OPENGL_COMMON_PROGRAM_HOLDERS_HPP
