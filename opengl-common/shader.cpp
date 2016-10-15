#define GLEW_STATIC
#include <GL/glew.h>

#include "opengl-common/shader.hpp"
#include "opengl-common/exceptions.hpp"
#include "opengl-common/misc.hpp"
#include "shader-holders.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/filename.h>
#include <wx/glcanvas.h>
#include <wx/stdpaths.h>
#include <algorithm>
#include <memory>
#include <string>

namespace kal {
namespace gl {

using namespace internal;

Shader Shader::FromRawShader(GLuint shader)
{
    return Shader { std::make_unique<RawShaderHolder>(shader) };
}

Shader Shader::FromFile(GLenum shaderType, const char* const filename)
{
    Shader s { std::make_unique<ManagedShaderHolder>(shaderType) };
    s.SourceFromFile(filename);
    return s;
}

Shader::Shader::Shader():
    m_holder(nullptr)
{}

Shader::Shader(const Shader &obj):
    m_holder(nullptr)
{
    if (obj.m_holder) {
        m_holder = std::unique_ptr<IShaderHolder>(obj.m_holder->Clone());
    }
}

Shader::Shader(std::unique_ptr<IShaderHolder> &&holder):
    m_holder(std::move(holder))
{}

Shader::~Shader()
{}

Shader &Shader::operator=(const Shader &obj)
{
    Shader temp { obj };
    this->Swap(temp);
    return *this;
}

void Shader::Swap(Shader &rhs)
{
    using std::swap;
    swap(m_holder, rhs.m_holder);
}

GLuint Shader::Get() const
{
    return m_holder->Get();
}

Shader &Shader::Source(
    const size_t count,
    const char* const string[],
    const int size[])
{
    glShaderSource(Get(), count, string, size);
    return *this;
}

Shader &Shader::SourceFromFile(const char* const filename)
{
    wxFileName shaderPath { GetResourcePath() };
    shaderPath.AppendDir(wxT("shaders"));
    shaderPath.SetFullName(filename);

    if (!shaderPath.IsFileReadable()) {
        throw FileException { "the file is not readable" };
    }

    wxFile shaderFile;
    if (!shaderFile.Open(shaderPath.GetFullPath(), wxFile::read)) {
        throw FileException { "failed to open the file" };
    }

    wxString shaderText;
    if (!shaderFile.ReadAll(&shaderText)) {
        throw FileException { "failed to read the file" };
    }

    Source(shaderText.c_str().AsChar());
    return *this;
}

Shader &Shader::Compile()
{
    std::string info;
    glCompileShader(Get());

    GLsizei logLength;
    glGetShaderiv(Get(), GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1) {
        info.resize(logLength);

        GLsizei readLength;
        glGetShaderInfoLog(Get(), logLength, &readLength, &info[0]);
    }

    GLint status;
    glGetShaderiv(Get(), GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        if (info.empty()) {
            info = "unknown error";
        }
        throw ShaderCompileException { &info[0] };
    }

    return *this;
}

}} // kal::gl