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
	explicit Canvas(wxWindow *parent);


private:
	std::unique_ptr<wxGLContext> m_context;

	void OnPaint(wxPaintEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

}

#endif//GRAPHICS_CANVAS_HPP