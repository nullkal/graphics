#define GLEW_STATIC
#include <GL/glew.h>

#include "utils.hpp"
#include "config.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <cstdio>
#include <wx/filename.h>
#include <wx/stdpaths.h>

namespace kal {

wxString GetResourcePath()
{
    auto stdPaths = wxStandardPaths::Get();
    wxFileName execPath { stdPaths.GetExecutablePath() };

    wxFileName resourcePath { execPath.GetPath(), "" };
    resourcePath.RemoveLastDir();
    resourcePath.AppendDir("share");
    resourcePath.AppendDir(APP_NAME);
    return resourcePath.GetFullPath();
}

bool ShaderSourceFromFile(GLuint shader, const char *filename)
{
    wxFileName shaderPath { GetResourcePath() };
    shaderPath.AppendDir("shaders");
    shaderPath.SetFullName(filename);
    
    if (!shaderPath.IsFileReadable()) {
        return false;
    }

    wxFile shaderFile;
    if (!shaderFile.Open(shaderPath.GetFullPath(), wxFile::read))
    {
        return false;
    }

    wxString shaderText;
    if (!shaderFile.ReadAll(&shaderText))
    {
        return false;
    }

    const char* s[] { shaderText.c_str().AsChar() };
    glShaderSource(shader, 1, s, nullptr);

    return true;
}

void printShaderInfoLog(GLuint shader)
{
    GLsizei bufSize;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1) {
        GLchar *infoLog = (GLchar *)malloc(bufSize);

        if (infoLog != NULL) {
            GLsizei length;

            glGetShaderInfoLog(shader, bufSize, &length, infoLog);
            wxMessageBox(infoLog);
            free(infoLog);
        }
        else
            fprintf(stderr, "Could not allocate InfoLog buffer.\n");
    }
}

} // kal
