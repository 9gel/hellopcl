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
/// \class vesKiwiTestHelper
/// \ingroup kiwi
/// \brief A class that provides common testing methods using GLUT.
//
/// This class provides common helper methods for testing kiwi on the desktop
/// using GLUT to provide windows and mouse/keyboard.
#ifndef __vesKiwiTestHelper_h
#define __vesKiwiTestHelper_h

#include "vesTestHelper.h"
#include "vesKiwiBaseApp.h"
#include "vesKiwiBaselineImageTester.h"

class vesKiwiTestHelper : public vesTestHelper {
public:

  vesKiwiTestHelper() :
    IsTesting(false)
  {
  }

  ~vesKiwiTestHelper()
  {
  }

  vesKiwiBaseApp::Ptr app() {
    return this->mApp;
  }

  void setApp(vesKiwiBaseApp::Ptr app) {
    this->mApp = app;
  }

  std::string sourceDirectory() {
    return this->SourceDirectory;
  }

  void setSourceDirectory(std::string dir) {
    this->SourceDirectory = dir;
  }

  std::string dataDirectory() {
    return this->DataDirectory;
  }

  void setDataDirectory(std::string dir) {
    this->DataDirectory = dir;
  }

  bool isTesting() {
    return this->IsTesting;
  }

  void setTesting(bool testing) {
    this->IsTesting = testing;
  }

  void render()
  {
    this->app()->render();
    glutSwapBuffers();
  }

  void resize(int width, int height)
  {
    this->app()->resizeView(width, height);
  }

  virtual void resetView()
  {
    this->app()->resetView();
  }

  void handleLeftClickDown(int x, int y)
  {
    this->app()->handleSingleTouchDown(x, y);
  }

  void handleLeftClickUp(int x, int y)
  {
    this->app()->handleSingleTouchUp();
  }

  void handleMouseMotion(int x, int y)
  {
    if (mIsLeftClick) {
      if (mIsShiftKey) {
        this->app()->handleTwoTouchPanGesture(mLastMousePositionX, this->app()->viewHeight() - mLastMousePositionY, x, this->app()->viewHeight() - y);
      }
      else {
        this->app()->handleSingleTouchPanGesture(x - mLastMousePositionX, y - mLastMousePositionY);
      }
    }
    else {
      double dist = static_cast<double>(y - mLastMousePositionY) / this->app()->viewHeight();
      this->app()->handleTwoTouchPinchGesture(1.0 + dist);
    }

    vesTestHelper::handleMouseMotion(x, y);
  }

  void handleKeyboard(unsigned char key, int x, int y)
  {
    if (key == 'r') {
      this->resetView();
    }
    else {
      vesTestHelper::handleKeyboard(key, x, y);
    }
  }

  bool performBaselineImageTest(const std::string& imageName)
  {
    const double threshold = 10.0;
    vesKiwiBaselineImageTester baselineTester;
    baselineTester.setApp(&*this->app());
    baselineTester.setBaselineImageDirectory(this->dataDirectory());
    return baselineTester.performTest(imageName, threshold);
  }

  static int main(int argc, char *argv[], vesKiwiTestHelper &helper)
  {
    if (argc < 2) {
      printf("Usage: %s <path to VES source directory> [path to testing data directory]\n", argv[0]);
      return 1;
    }

    helper.setSourceDirectory(argv[1]);
    if (argc == 3) {
      helper.setDataDirectory(argv[2]);
      helper.setTesting(true);
    }

    const int windowWidth = 800;
    const int windowHeight = 600;
    helper.init(&argc, argv, windowWidth, windowHeight, argv[0]);
    helper.app()->initGL();
    if (!helper.initTesting()) {
      return 1;
    }

    // render once
    helper.resize(windowWidth, windowHeight);
    helper.resetView();
    helper.app()->render();

    // begin the event loop if not in testing mode
    bool testPassed = true;
    if (!helper.isTesting()) {
      helper.startMainLoop();
    }
    else {
      testPassed = helper.doTesting();
    }

    return testPassed ? 0 : 1;
  }


private:

  vesKiwiBaseApp::Ptr  mApp;
  std::string          SourceDirectory;
  std::string          DataDirectory;
  bool                 IsTesting;
};




#endif
