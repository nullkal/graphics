/**
 * @file   misc.hpp
 * @author nullkal <nullkal@nil.nu>
 *
 * @brief  declares various library functions.
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

/**
 * @brief Initialize wxGLContext.
 * 
 * This function initializes the wxGLContext object and returns wrapperd
 * in the std::shared_ptr. This function also initializes GLEW, so in the
 * context this function returns you can use OpenGL extensions with GLEW.
 *
 * @param[in] p  The parent window.
 * @param[in] glAttrs  The wxGLAttributes of the canvas in which the
 *                     context should be made.
 * @param[in] ctxAttrs  The wxGLContextAttrs of the context.
 * @return The shared_ptr-wrapped wxGLContext object. When this function
 *         failes, nullptr is returned.
 *
 * @note You don't need to call wxGLContext::IsOK() since this function
 *       returns nullptr if the initialization is failed.
 */
std::shared_ptr<wxGLContext> initGLContext(
    wxWindow* const p,
    const wxGLAttributes &glAttrs,
    const wxGLContextAttrs &ctxAttrs);

/**
 * @brief Return the resource path.
 *
 * This function returns the path in which the resources should be placed.
 *
 * More specifically, it returns `../share/{wxTheApp->GetAppName()}/`
 * relative to the directory the executable file is deployed.
 *
 * @return The resource path.
 */
wxString GetResourcePath();

}} // kal::gl

#endif//OPENGL_COMMON_MISC_HPP
