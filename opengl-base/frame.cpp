#include "frame.hpp"

#include "app.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>

namespace kal {
namespace {

std::shared_ptr<wxGLContext> createContext(wxWindow *p, const wxGLAttributes &attrs) {
	auto c = new wxGLCanvas(p, attrs); // a wxGLCanvas is needed to initialize wxGLContext
	auto ctx = std::make_shared<wxGLContext>(c);

	c->Destroy();
	return ctx;
}

}

Frame::Frame():
	wxFrame(nullptr, wxID_ANY, APPNAME)
{
	wxGLAttributes attrs;
	attrs
		.PlatformDefaults()
		.MinRGBA(8, 8, 8, 8)
		.Depth(16)
		.DoubleBuffer()
		.EndList();
	auto ctx = createContext(this, attrs);

	m_canvas = new Canvas { this, attrs, ctx };
}

}