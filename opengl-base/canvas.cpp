#include "canvas.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifdef APPLE
#include <OpenGL/GL.h>
#else
#include <gl/GL.h>
#endif

namespace kal {
namespace {

const int CANVAS_ATTRIBUTES[] = {
	WX_GL_RGBA,
	WX_GL_DOUBLEBUFFER,
	0
};

}

wxBEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
	EVT_PAINT(Canvas::OnPaint)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow *parent):
	wxGLCanvas(parent, wxID_ANY, CANVAS_ATTRIBUTES),
	m_context(std::make_unique<wxGLContext>(this))
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

void Canvas::OnPaint(wxPaintEvent &evt)
{
	if (!this->IsShown()) {
		return;
	}

	wxGLCanvas::SetCurrent(*m_context);
	wxPaintDC(this);

	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
	SwapBuffers();
}

}