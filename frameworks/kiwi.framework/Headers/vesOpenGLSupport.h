#ifndef VESOPENGLSUPPORT_H
#define VESOPENGLSUPPORT_H
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

#include "vesSetGet.h"

// C/C++ includes
#include <set>
#include <string>

class vesOpenGLSupport
{
public:
  vesTypeMacro(vesOpenGLSupport);

  vesOpenGLSupport();
  ~vesOpenGLSupport();

  void initialize();

  bool isInitialized()
  {
    return m_initialized;
  }

  const std::string& glVendor() const
  {
    return m_vendor;
  }

  const std::string& glVersion(void) const
  {
    return m_version;
  }

  bool isSupported(const std::string& ext) const;

  bool isSupportedIndexUnsignedInt() const;

private:


  bool m_initialized;

  std::string m_version;
  std::string m_vendor;

  std::set<std::string> m_extensionList;
};

#endif // VESOPENGLSUPPORT_H
