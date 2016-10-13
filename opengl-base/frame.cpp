#define GLEW_STATIC
#include <GL/glew.h>

#include "frame.hpp"
#include "app.hpp"
#include "config.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>

namespace kal {
namespace {

std::shared_ptr<wxGLContext> initGLContext(
    wxWindow *p,
    const wxGLAttributes &glAttrs,
    const wxGLContextAttrs &ctxAttrs)
{
    auto c = new wxGLCanvas(p, glAttrs); // wxGLCanvas is needed to initialize wxGLContext
    auto ctx = std::make_shared<wxGLContext>(c, nullptr, &ctxAttrs);

    c->SetCurrent(*ctx);
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        wxString errStr = wxT("Failed to initialize GLEW: ") + wxString(glewGetErrorString(err));
        wxMessageBox(errStr, APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
    }

    c->Destroy();
    return ctx;
}

} // kal::(anonymous)

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

    auto ctx = initGLContext(this, glAttrs, ctxAttrs);
    if (!(ctx && ctx->IsOK())) {
        wxMessageBox(wxT("Couldn't create the OpenGL context."), APP_NAME, wxOK | wxICON_ERROR);
        wxExit();
    }

    m_canvas = new Canvas { this, glAttrs, ctx };
}

} // kal