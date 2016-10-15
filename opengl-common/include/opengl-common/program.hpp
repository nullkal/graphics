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

class Program {
public:
    static Program FromRawProgram(GLuint program);

    Program();
    Program(const Program &obj);

    ~Program();

    Program &operator=(const Program &obj);

    operator GLuint() const;

    void Swap(Program &rhs);

    GLuint Get() const;

    void Use() const;

    Program &AttachShader(const Shader &shader);

    Program &Link();

private:
    std::unique_ptr<internal::IProgramHolder> m_holder;

    Program(std::unique_ptr<internal::IProgramHolder> &&holder);
};

class ProgramLinkException : public std::exception {
public:
    explicit ProgramLinkException(const char* const message):
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

#endif//OPENGL_COMMON_PROGRAM_HPP
