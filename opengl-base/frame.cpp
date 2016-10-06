#include "frame.hpp"

#include "app.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

Frame::Frame():
	wxFrame(nullptr, wxID_ANY, APPNAME)
{
	m_canvas = new Canvas { this };
}

}