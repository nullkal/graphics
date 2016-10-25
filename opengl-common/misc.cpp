/**
* @file   misc.cpp
* @author nullkal <nullkal@nil.nu>
*
* @brief  implements various library functions.
*/

/*
* Copyright (c) 2016 nullkal <nullkal@nil.nu>
*
* This file is distributed under the MIT License.
* See LICENSE for more information.
*/

#define GLEW_STATIC
#include <GL/glew.h>

#include "opengl-common/misc.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/filename.h>
#include <wx/glcanvas.h>
#include <wx/stdpaths.h>
#include <memory>

namespace kal {
namespace gl {

std::shared_ptr<wxGLContext> initGLContext(
    wxWindow* const p,
    const wxGLAttributes &glAttrs,
    const wxGLContextAttrs &ctxAttrs)
{
    const auto canvasDeleter = [](wxGLCanvas *obj) { obj->Destroy(); };
    auto c = std::unique_ptr<wxGLCanvas, decltype(canvasDeleter)>(
        new wxGLCanvas(p, glAttrs),
        canvasDeleter); // wxGLCanvas is needed to initialize wxGLContext
    auto ctx = std::make_shared<wxGLContext>(c.get(), nullptr, &ctxAttrs);

    if (!ctx->IsOK()) {
        return nullptr;
    }

    c->SetCurrent(*ctx);
    const GLenum err = glewInit();
    if (err != GLEW_OK) {
        wxLogError(wxT("Failed to initialize GLEW: ") + wxString(glewGetErrorString(err)));
        return nullptr;
    }

    return ctx;
}

wxString GetResourcePath()
{
    const auto stdPaths = wxStandardPaths::Get();
    const wxFileName execPath{ stdPaths.GetExecutablePath() };

    wxFileName resourcePath{ execPath.GetPath(), wxT("") };
    resourcePath.RemoveLastDir();
    resourcePath.AppendDir(wxT("share"));
    resourcePath.AppendDir(wxTheApp->GetAppName());
    return resourcePath.GetFullPath();
}

}} // kal::gl