#ifndef GRAPHICS_UTILS_HPP
#define GRAPHICS_UTILS_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace kal {

wxString GetResourcePath();

bool ShaderSourceFromFile(GLuint shader, const char *filename);
void printShaderInfoLog(GLuint shader);

} // kal

#endif//GRAPHICS_UTILS_HPP
