#ifndef GRAPHICS_CANVAS_HPP
#define GRAPHICS_CANVAS_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/glcanvas.h>
#include <memory>

namespace kal {

class Canvas : public wxGLCanvas {
public:
	Canvas(wxWindow *parent, const wxGLAttributes &attrs, std::shared_ptr<wxGLContext> ctx);


private:
	std::shared_ptr<wxGLContext> m_context;

	void OnPaint(wxPaintEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

}

#endif//GRAPHICS_CANVAS_HPP