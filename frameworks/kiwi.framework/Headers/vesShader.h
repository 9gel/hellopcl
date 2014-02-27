/*========================================================================
  VES --- VTK OpenGL ES Rendering Toolkit

      http://www.kitware.com/ves

  Copyright 2011 Kitware, Inc.
  Copyright 2012 Willow Garage, Inc.

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
/// \class vesShader
/// \ingroup ves
/// \see vesShader vesShaderProgram vesMaterial

#ifndef VESSHADER_H
#define VESSHADER_H

// VES includes
#include "vesGL.h"
#include "vesSetGet.h"

// C/C++ includes
#include <string>

class vesShader
{
public:
  vesTypeMacro(vesShader);

  // \note: GL* types can be moved to some external header.
  enum ShaderType
  {
    Vertex = GL_VERTEX_SHADER,

    // \note: Currently GLES does not support other shaders.
    //TESSCONTROL    = GL_TESS_CONTROL_SHADER,
    //TESSEVALUATION = GL_TESS_EVALUATION_SHADER,
    //GEOMETRY       = GL_GEOMETRY_SHADER_EXT,

    Fragment = GL_FRAGMENT_SHADER,
    Undefined = -1
  };


  vesShader(ShaderType type = Undefined);
  vesShader(ShaderType type, const std::string &source);
  virtual ~vesShader();

  // \todo: Implement these useful functions.
  // int compare(const vesShader &rhs);

  inline unsigned int shaderHandle() { return this->m_shaderHandle; }

  bool setShaderType(ShaderType type);
  inline ShaderType shaderType() const
  {
    return m_type;
  }

  inline void setFileName(const std::string &fileName)
  {
    this->m_shaderFileName = fileName;

    // \todo: Make state dirty.
  }

  inline const std::string& fileName() const
  {
    return this->m_shaderFileName;
  }

  inline void setShaderSource(const std::string &sourceText)
  {
    this->m_shaderSource = sourceText;

    // \todo: Make state dirty.
  }

  inline const std::string &shaderSource() const
  {
    return this->m_shaderSource;
  }

  // If needed, compile the PC shader.
  void compileShader();

  // Attach a glShader to a glProgram.
  void attachShader(unsigned int program) const;

  // For a given GL context, attach a glShader to a glProgram.
  // \todo: Improvement (support per context shader).
  // void attachShader(unsigned int contextID, GLuint program) const;

  // \todo: Implement this.
  // bool loadShaderSourceFromFile(const std::string &fileName);

  // For a given GL context, detach a glShader to a glProgram.
  // \todo: Implement this.
  // void detachShader(unsigned int contextID, GLuint program) const;

  // Query InfoLog from a shader.
  // \todo: Implement this.
  // bool getShaderInfoLog(unsigned int contextID, std::string &log) const;

protected:
  ShaderType m_type;

  unsigned int m_shaderHandle;

  std::string m_shaderFileName;

  std::string m_shaderSource;
};

#endif
