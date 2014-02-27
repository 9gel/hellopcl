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
/// \class vesKiwiDataLoader
/// \ingroup KiwiPlatform
#ifndef __vesKiwiDataLoader_h
#define __vesKiwiDataLoader_h

#include <string>
#include <vtk/vtkSmartPointer.h>

class vtkAlgorithm;
class vtkDataSet;

class vesKiwiDataLoader
{
public:

  vesKiwiDataLoader();
  ~vesKiwiDataLoader();

  /// Set/get whether or not this class should throw an error when loading
  /// datasets with more than 65k vertices.  Note, if the loaded data contains
  /// only vertices and no primitives (lines, triangles, etc), than no error
  /// will be thrown even if this setting is enabled.  The default setting is
  /// enabled- an error will be thrown.  If the GL context has support for the
  /// GL_OES_element_index_uint extension, then it is safe to disable this error.
  void setErrorOnMoreThan65kVertices(bool isEnabled);
  bool isErrorOnMoreThan65kVertices() const;

  vtkSmartPointer<vtkDataSet> loadDataset(const std::string& filename);
  std::string errorTitle() const;
  std::string errorMessage() const;

  static bool hasEnding(const std::string& fullString, const std::string& ending);

protected:

  /// Update the given algorithm and return the output dataset.  If the output
  /// dataset is not vtkPolyData or vtkImageData then this method will apply
  /// a surface filter and return the result of the surface filter instead.
  vtkSmartPointer<vtkDataSet> datasetFromAlgorithm(vtkAlgorithm* algorithm);


  bool updateAlgorithmOrSetErrorString(vtkAlgorithm* algorithm);
  void setMaximumNumberOfPointsErrorMessage();

private:

  vesKiwiDataLoader(const vesKiwiDataLoader&); // Not implemented
  void operator=(const vesKiwiDataLoader&); // Not implemented

  class vesInternal;
  vesInternal* Internal;
};


#endif
