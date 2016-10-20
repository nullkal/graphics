/**
 * @file   program-holders.cpp
 * @author nullkal <nullkal@nil.nu>
 *
 * @brief  implements IProgramHolder, ManagedProgramHolder, and RawProgramHolder.
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#define GLEW_STATIC
#include <GL/glew.h>

#include "program-holders.hpp"

#include <algorithm>
namespace kal {
namespace gl {
namespace internal {

ManagedProgramHolder::ManagedProgramHolder():
    m_refCount(new int(1)),
    m_program(glCreateProgram())
{
    // FIXME: throw an exception if this constructor fails to create a shader
}

ManagedProgramHolder::ManagedProgramHolder(const ManagedProgramHolder &obj):
    m_refCount(obj.m_refCount),
    m_program(obj.m_program)
{
    ++(*m_refCount);
}

ManagedProgramHolder &ManagedProgramHolder::operator=(const ManagedProgramHolder &obj)
{
    using namespace std;

    ManagedProgramHolder temp(obj);
    swap(*this, temp);

    return *this;
}

ManagedProgramHolder::~ManagedProgramHolder()
{
    --(*m_refCount);
    if (*m_refCount <= 0) {
        delete m_refCount;
        glDeleteProgram(m_program);
    }
}

ManagedProgramHolder* ManagedProgramHolder::Clone() const
{
    return new ManagedProgramHolder{ *this };
}

GLuint ManagedProgramHolder::Get() const
{
    return m_program;
}

RawProgramHolder::RawProgramHolder(GLuint program) :
    m_program(program)
{}

RawProgramHolder* RawProgramHolder::Clone() const
{
    return new RawProgramHolder { *this };
}

GLuint RawProgramHolder::Get() const
{
    return m_program;
}

}}} // kal::gl::internal
