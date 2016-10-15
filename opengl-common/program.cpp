#define GLEW_STATIC
#include <GL/glew.h>

#include "opengl-common/program.hpp"
#include "opengl-common/shader.hpp"
#include "program-holders.hpp"

#include <algorithm>
#include <memory>
#include <string>

namespace kal {
namespace gl {

using namespace internal;

Program Program::FromRawProgram(GLuint program)
{
    return Program { std::make_unique<RawProgramHolder>(program) };
}

Program::Program():
    m_holder(std::make_unique<ManagedProgramHolder>())
{}

Program::Program(const Program &obj):
    m_holder(nullptr)
{
    if (obj.m_holder) {
        m_holder = std::unique_ptr<IProgramHolder>(obj.m_holder->Clone());
    }
}

Program::Program(std::unique_ptr<IProgramHolder> &&holder):
    m_holder(std::move(holder))
{}

Program::~Program()
{}

Program &Program::operator=(const Program &obj)
{
    Program temp{ obj };
    this->Swap(temp);
    return *this;
}

Program::operator GLuint() const
{
    return Get();
}

void Program::Swap(Program &rhs)
{
    using std::swap;
    swap(m_holder, rhs.m_holder);
}

GLuint Program::Get() const
{
    return m_holder->Get();
}

void Program::Use() const
{
    glUseProgram(Get());
}

Program &Program::AttachShader(const Shader &shader)
{
    glAttachShader(Get(), shader.Get());
    return *this;
}

Program &Program::Link()
{
    std::string info;
    glLinkProgram(Get());

    GLsizei logLength;
    glGetProgramiv(Get(), GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1) {
        info.resize(logLength);

        GLsizei readLength;
        glGetProgramInfoLog(Get(), logLength, &readLength, &info[0]);
    }

    GLint status;
    glGetProgramiv(Get(), GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        if (info.empty()) {
            info = "unknown error";
        }
        throw ProgramLinkException { &info[0] };
    }

    return *this;
}

}} // kal::gl