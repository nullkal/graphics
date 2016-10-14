#define GLEW_STATIC
#include <GL/glew.h>

#include "canvas.hpp"
#include "config.hpp"

#include <opengl-common/exceptions.hpp>
#include <opengl-common/shader.hpp>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {
namespace {

struct Position {
    GLfloat x, y, z;
};

} // kal::(anonymous)

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
    wxGLCanvas::SetCurrent(*m_context);

    gl::Shader vertexShader, fragmentShader;
    try {
        vertexShader   = gl::Shader::FromFile(GL_VERTEX_SHADER, "sample.vert").Compile();
        fragmentShader = gl::Shader::FromFile(GL_FRAGMENT_SHADER, "sample.frag").Compile();
    }
    catch (gl::FileException &e) {
        wxLogFatalError(wxT("Failed to load the shader: ") + wxString(e.what()));
    }
    catch (gl::ShaderCompileException &e) {
        wxLogFatalError(wxT("Failed to compile the shader: ") + wxString(e.what()));
    }

    m_glProgram = glCreateProgram();
    glAttachShader(m_glProgram, vertexShader.Get());
    glAttachShader(m_glProgram, fragmentShader.Get());

    glBindAttribLocation(m_glProgram, 0, "position");

    glLinkProgram(m_glProgram);

    GLint linked;
    glGetProgramiv(m_glProgram, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        wxMessageBox("Failed to link shaders", APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
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

    glUseProgram(m_glProgram);

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