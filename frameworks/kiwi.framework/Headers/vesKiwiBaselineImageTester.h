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
/// \class vesKiwiBaselineImageTester
/// \ingroup KiwiPlatform
/// \brief A class for testing rendered images against baseline images
//
/// This class uses the vtk filter vtkImageDifference to test rendered images
/// against baseline images.  It uses a GL call to fetch pixels from the
/// current GL context and converts them to a vtkImageData for comparison.
/// This class also performs I/O to read baseline images and write difference images.
#ifndef __vesKiwiBaselineImageTester_h
#define __vesKiwiBaselineImageTester_h

#include <vtk/vtkSmartPointer.h>

class vtkImageData;
class vesKiwiBaseApp;

class vesKiwiBaselineImageTester
{
public:

  vesKiwiBaselineImageTester();

  ~vesKiwiBaselineImageTester();

  /// Return the currently set vesKiwiBaseApp.
  vesKiwiBaseApp* app();

  /// Set the vesKiwiBaseApp to be tested.  Currently, the vesKiwiBaseApp instance is used
  /// to get the current screen width and height in order to convert the pixel buffer to
  /// a vtkImageData.
  void setApp(vesKiwiBaseApp* app);

  /// Get the directory where baseline images are stored.
  const std::string& baselineImageDirectory();

  /// Set the directory where baseline images are stored.
  void setBaselineImageDirectory(const std::string& baselineImageDirectory);

  /// Uses the vtkPNGReader to load a vtkImageData from a PNG image stored at the given
  /// filename.  The filename must be a PNG image.  Returns the output of the reader.
  vtkSmartPointer<vtkImageData> imageFromFile(const std::string& filename);

  /// Uses the GL call glReadPixels to read GL_RGB pixels from the current context and
  /// returns the result as a vtkImageData.  The width and height of the pixel buffer is
  /// determined by the current vesKiwiBaseApp.
  /// \see setApp()
  /// \see vesKiwiBaseApp::viewWidth()
  /// \see vesKiwiBaseApp::viewHeight()
  vtkSmartPointer<vtkImageData> imageFromRenderView();

  /// Uses the vtkPNGWriter to write the save the given vtkImageData with the given filename.
  void writeImage(vtkImageData* image, const std::string& filename);

  /// Performs a baselime image comparison using the vtkImageDifference filter.  This looks for
  /// a baseline image with a png extension and filename matching the given testName.  It looks in
  /// the baseline image directory.   Returns true if the image difference is within the given threshold.
  /// Otherwise, returns false, and writes the difference image to the current working directory.
  bool performTest(const std::string& testName, double threshold);

protected:

  std::string mBaselineImageDirectory;
  vesKiwiBaseApp* mApp;

};

#endif
