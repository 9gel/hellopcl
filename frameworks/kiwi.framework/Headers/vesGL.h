/*========================================================================
  VES --- VTK OpenGL ES Rendering Toolkit

      http://www.kitware.com/ves

  Copyright 2011 Kitware, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 ========================================================================*/
#ifndef VESGL_H
#define VESGL_H

#ifdef VES_USE_DESKTOP_GL
  // Setup for desktop GL
  #ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glext.h>
  #else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
  #endif
  #define glClearDepthf glClearDepth
#else
  // Setup for OpenGL ES
  #ifdef __APPLE__
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
  #else
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
  #endif
#endif

#ifndef GL_SAMPLER_1D
    #define GL_SAMPLER_1D               0x8B5D
    #define GL_SAMPLER_2D               0x8B5E
    #define GL_SAMPLER_3D               0x8B5F
    #define GL_SAMPLER_1D_SHADOW        0x8B61
    #define GL_SAMPLER_2D_SHADOW        0x8B62
#endif


#define flushGLError(os, glEnum) \
{ \
  os << "ERROR: Occured in " << __FILE__ << " at line " << __LINE__ << " (error code: " << #glEnum << ")\n"; \
} \


#define printGLErrorEnum(os, error) \
{ \
  switch(error) \
  { \
    case GL_INVALID_ENUM: { flushGLError(os, GL_INVALID_ENUM); break; } \
    case GL_INVALID_FRAMEBUFFER_OPERATION: { flushGLError(os, GL_INVALID_FRAMEBUFFER_OPERATION); break; } \
    case GL_INVALID_VALUE: { flushGLError(os, GL_INVALID_VALUE); break; } \
    case GL_INVALID_OPERATION: { flushGLError(os, GL_INVALID_OPERATION); break; } \
    case GL_OUT_OF_MEMORY: { flushGLError(os, GL_OUT_OF_MEMORY); break; } \
  }; \
} \


#define printGLError(os) \
{ \
  GLenum error = glGetError(); \
  if (error != GL_NO_ERROR) { \
    printGLErrorEnum(os, error); \
  } \
} \


#define printGLErrorWithMessage(message, os) \
{ \
  GLenum error = glGetError(); \
  if (error != GL_NO_ERROR) { \
    os << message << "\n"; \
    printGLErrorEnum(os, error); \
  } \
} \


#endif
