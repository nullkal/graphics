#include "app.hpp"

#include "frame.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

const char *APPNAME = "OpenGL-Base";

bool App::OnInit()
{
	if (!wxApp::OnInit()) {
		return false;
	}

	wxFrame *frame = new Frame;
	frame->Show(true);

    return true;
}

}

wxIMPLEMENT_APP(kal::App);
