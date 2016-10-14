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
    ~Canvas();

private:
    std::shared_ptr<wxGLContext> m_context;

    wxStopWatch m_stopWatch;

    GLuint m_glProgram;
    GLuint m_vertexArray;
	
    void OnPaint(wxPaintEvent &evt);
    void OnIdle(wxIdleEvent &evt);
    void OnResize(wxSizeEvent &evt);

    double CurrentTime() { return m_stopWatch.TimeInMicro().GetValue() / 1000000.; }

    wxDECLARE_EVENT_TABLE();
};

} // kal

#endif//GRAPHICS_CANVAS_HPP