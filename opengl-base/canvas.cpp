#define GLEW_STATIC
#include <GL/glew.h>

#include "canvas.hpp"

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

}

wxBEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
    EVT_PAINT(Canvas::OnPaint)
    EVT_IDLE(Canvas::OnIdle)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow *parent, const wxGLAttributes &attrs, std::shared_ptr<wxGLContext> ctx):
    wxGLCanvas(parent, attrs),
    m_context(ctx),
    m_stopWatch()
{
    GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    m_glProgram = glCreateProgram();
    glAttachShader(m_glProgram, vertexShader);
    glAttachShader(m_glProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glBindAttribLocation(m_glProgram, 0, "position");

    GLint linked;
    glLinkProgram(m_glProgram);
    glGetProgramiv(m_glProgram, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        fprintf(stderr, "Link error.\n");
        exit(1);
    }

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Position) * 3, NULL, GL_STATIC_DRAW);
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

    const GLfloat black[] = {
        static_cast<float>(std::sin(CurrentTime())) * 0.5f + 0.5f,
        static_cast<float>(std::cos(CurrentTime())) * 0.5f + 0.5f,
        0.f,
        1.f
    };
    glClearBufferfv(GL_COLOR, 0, black);

    glFlush();
    SwapBuffers();
}

void Canvas::OnIdle(wxIdleEvent &evt)
{
    Refresh();
    evt.RequestMore();
}

} // kal