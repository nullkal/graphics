#define GLEW_STATIC
#include <GL/glew.h>

#include "canvas.hpp"
#include "config.hpp"
#include "utils.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <cmath>

namespace kal {
namespace {

struct Position {
    GLfloat x, y, z;
};

} // kal::(anonymous)

wxBEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
    EVT_PAINT(Canvas::OnPaint)
    EVT_IDLE(Canvas::OnIdle)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow *parent, const wxGLAttributes &attrs, std::shared_ptr<wxGLContext> ctx):
    wxGLCanvas(parent, attrs),
    m_context(ctx),
    m_stopWatch()
{
    GLint compiled, linked;
    this->SetCurrent(*ctx);

    GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
    if (!ShaderSourceFromFile(vertexShader, "sample.vert")) {
        wxMessageBox("Failed to load the vertex shader", APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
    }
    glCompileShader(vertexShader);
    printShaderInfoLog(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        wxMessageBox("Failed to compile the vertex shader", APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!ShaderSourceFromFile(fragmentShader, "sample.frag")) {
        wxMessageBox("Failed to load the fragment shader", APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
    }
    glCompileShader(fragmentShader);
    printShaderInfoLog(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        wxMessageBox("Failed to compile the fragment shader", APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
    }

    m_glProgram = glCreateProgram();
    glAttachShader(m_glProgram, vertexShader);
    glAttachShader(m_glProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glBindAttribLocation(m_glProgram, 0, "position");

    glLinkProgram(m_glProgram);
    glGetProgramiv(m_glProgram, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        wxMessageBox("Failed to link shaders", APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
    }

    glGenVertexArrays(1, &m_vertexArray);
}

Canvas::~Canvas()
{

}

void Canvas::OnPaint(wxPaintEvent &evt)
{
    if (!this->IsShown()) {
        return;
    }

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this);

    const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, black);

    int width, height;
    GetClientSize(&width, &height);
    glViewport(0, 0, width, height);

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

} // kal