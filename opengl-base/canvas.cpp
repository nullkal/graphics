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

wxBEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
	EVT_PAINT(Canvas::OnPaint)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow *parent, const wxGLAttributes &attrs, std::shared_ptr<wxGLContext> ctx):
	wxGLCanvas(parent, attrs),
	m_context(ctx)
{}

void Canvas::OnPaint(wxPaintEvent &evt)
{
	if (!this->IsShown()) {
		return;
	}

	wxGLCanvas::SetCurrent(*m_context);
	wxPaintDC(this);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
	SwapBuffers();
}

}