#ifndef OPENGL_COMMON_MISC_HPP
#define OPENGL_COMMON_MISC_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/glcanvas.h>
#include <memory>

namespace kal {
namespace gl {

std::shared_ptr<wxGLContext> initGLContext(
    wxWindow* const p,
    const wxGLAttributes &glAttrs,
    const wxGLContextAttrs &ctxAttrs);

wxString GetResourcePath();

}} // kal::gl

#endif//OPENGL_COMMON_MISC_HPP
