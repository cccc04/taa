#pragma once

#include <string.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <unistd.h>
#include <sys/resource.h>

#else // __ANDROID__ or _WIN32
#include <GLES2/gl2.h>
#endif

class SimpleRenderer
{
public:
    SimpleRenderer();
    ~SimpleRenderer();
    void Draw();
    void UpdateWindowSize(GLsizei width, GLsizei height);
    void SSS(const char* aa, const char* i);
    void sts(const char* st);
    const char* rts();
    bool yn();
    void ync();

private:
    GLuint mProgram;
    GLsizei mWindowWidth;
    GLsizei mWindowHeight;

    GLint mPositionAttribLocation;
    GLint mColorAttribLocation;

    GLint mModelUniformLocation;
    GLint mViewUniformLocation;
    GLint mProjUniformLocation;

    GLuint mVertexPositionBuffer;
    GLuint mVertexColorBuffer;
    GLuint mIndexBuffer;

    int mDrawCount;
};
