#include "app.hpp"
#include "frame.hpp"
#include "config.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

bool App::OnInit()
{
    if (!wxApp::OnInit()) {
        return false;
    }

    wxFrame *frame = new Frame;
    frame->Show(true);

    return true;
}

} // kal

wxIMPLEMENT_APP(kal::App);
