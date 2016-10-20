/**
 * @file   misc.hpp
 * @author nullkal <nullkal@nil.nu>
 *
 * @brief  declares various library functions
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

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
