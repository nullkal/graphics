#define GLEW_STATIC
#include <GL/glew.h>

#include "frame.hpp"
#include "app.hpp"
#include "canvas.hpp"
#include "config.hpp"

#include <opengl-common/misc.hpp>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>

namespace kal {

Frame::Frame():
    wxFrame(nullptr, wxID_ANY, APP_NAME)
{
    wxGLAttributes glAttrs;
    glAttrs
        .PlatformDefaults()
        .MinRGBA(8, 8, 8, 8)
        .Depth(24)
        .DoubleBuffer()
        .EndList();

    wxGLContextAttrs ctxAttrs;
    ctxAttrs
        .CoreProfile()
        .OGLVersion(3, 2)
        .Robust()
        .ResetIsolation()
        .EndList();

    const auto ctx = gl::initGLContext(this, glAttrs, ctxAttrs);
    if (!(ctx && ctx->IsOK())) {
        wxLogFatalError(wxT("Failed to create the OpenGL context."));
    }

    m_canvas = new Canvas { this, glAttrs, ctx };
}

} // kal