/**
 * @file   canvas.cpp
 * @author nullkal <nullkal@nil.nu>
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#define GLEW_STATIC
#include <GL/glew.h>

#include "canvas.hpp"

#include <opengl-common/exceptions.hpp>
#include <opengl-common/program.hpp>
#include <opengl-common/shader.hpp>

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

wxBEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
    EVT_PAINT(Canvas::OnPaint)
    EVT_IDLE(Canvas::OnIdle)
    EVT_SIZE(Canvas::OnResize)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow *parent, const wxGLAttributes &attrs, std::shared_ptr<wxGLContext> ctx):
    wxGLCanvas(parent, attrs),
    m_context(ctx),
    m_stopWatch()
{
    using namespace gl;
    wxGLCanvas::SetCurrent(*m_context);

    try {
        m_program = Program()
            .AttachShader(Shader::FromFile(GL_VERTEX_SHADER,   "sample.vert").Compile())
            .AttachShader(Shader::FromFile(GL_FRAGMENT_SHADER, "sample.frag").Compile());
        m_program.Link();
    }
    catch (FileException &e) {
        wxLogFatalError(wxT("Failed to load the shader: ") + wxString(e.what()));
    }
    catch (ShaderCompileException &e) {
        wxLogFatalError(wxT("Failed to compile the shader: ") + wxString(e.what()));
    }
    catch (ProgramLinkException &e) {
        wxLogFatalError(wxT("Failed to link the shaders: ") + wxString(e.what()));
    }

    glGenVertexArrays(1, &m_vertexArray);
}

Canvas::~Canvas()
{}

void Canvas::OnPaint(wxPaintEvent &evt)
{
    if (!this->IsShown()) {
        return;
    }

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this);

    const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, black);

    m_program.Use();

    glBindVertexArray(m_vertexArray);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    glFlush();
    SwapBuffers();
}

void Canvas::OnIdle(wxIdleEvent &evt)
{
    Refresh();
    evt.RequestMore();
}


void Canvas::OnResize(wxSizeEvent &evt)
{
    wxGLCanvas::SetCurrent(*m_context);

    int width, height;
    GetClientSize(&width, &height);
    glViewport(0, 0, width, height);
}

} // kal