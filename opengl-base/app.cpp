/**
 * @file   app.cpp
 * @author nullkal <nullkal@nil.nu>
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#include "app.hpp"
#include "config.hpp"
#include "frame.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

bool App::OnInit()
{
    if (!wxApp::OnInit()) {
        return false;
    }

    SetAppName(APP_NAME);

    m_frame = new Frame;
    m_logWindow = new wxLogWindow{ m_frame, wxT("Log - ") + wxString(APP_NAME) };

    m_frame->SetSize(640, 480);

    m_frame->Show(true);
    m_logWindow->Show(true);

    return true;
}

} // kal

wxIMPLEMENT_APP(kal::App);
