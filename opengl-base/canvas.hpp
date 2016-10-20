/**
 * @file   canvas.hpp
 * @author nullkal <nullkal@nil.nu>
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#ifndef GRAPHICS_CANVAS_HPP
#define GRAPHICS_CANVAS_HPP

#include <opengl-common/program.hpp>

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

    gl::Program m_program;
    GLuint m_vertexArray;
	
    void OnPaint(wxPaintEvent &evt);
    void OnIdle(wxIdleEvent &evt);
    void OnResize(wxSizeEvent &evt);

    double CurrentTime() { return m_stopWatch.TimeInMicro().GetValue() / 1000000.; }

    wxDECLARE_EVENT_TABLE();
};

} // kal

#endif//GRAPHICS_CANVAS_HPP