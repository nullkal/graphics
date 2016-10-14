#ifndef GRAPHICS_APP_HPP
#define GRAPHICS_APP_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

class Frame;

class App: public wxApp {
public:
    virtual bool OnInit();

private:
    Frame *m_frame;
    wxLogWindow *m_logWindow;
};

} // kal

wxDECLARE_APP(kal::App);

#endif//GRAPHICS_APP_HPP
