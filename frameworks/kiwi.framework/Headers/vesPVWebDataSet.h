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
/// \class vesPVWebDataSet
/// \ingroup KiwiPlatform
#ifndef __vesPVWebDataSet_h
#define __vesPVWebDataSet_h

#include <string>
#include <tr1/memory>

class vesPVWebDataSet
{
public:

  typedef std::tr1::shared_ptr<vesPVWebDataSet> Ptr;

  vesPVWebDataSet();
  ~vesPVWebDataSet();

  long long m_id;
  int m_part;
  int m_layer;
  int m_transparency;
  std::string m_md5;

  char* m_buffer;
  size_t m_writePosition;
  size_t m_bufferSize;

  int m_numberOfVerts;
  int m_numberOfIndices;
  char m_datasetType;

  float* vertices() const;

  float* normals() const;

  const float* matrix() const;

  short* indices() const;

  unsigned char* colors() const;

  void printSelf() const;

  void initFromBuffer();

  static vesPVWebDataSet::Ptr loadDataSetFromFile(const std::string& filename);

private:

  float* m_verts;
  short* m_indices;
  unsigned char* m_colors;
  float m_matrix[16];
};

#endif
