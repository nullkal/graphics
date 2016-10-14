#ifndef GRAPHICS_FRAME_HPP
#define GRAPHICS_FRAME_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

class Canvas;

class Frame : public wxFrame {
public:
    Frame();

private:
    Canvas *m_canvas;
};

} // kal

#endif//GRAPHICS_FRAME_HPP