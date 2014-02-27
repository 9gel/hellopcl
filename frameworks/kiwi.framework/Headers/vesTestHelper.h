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
/// \class vesTestHelper
/// \ingroup VES
/// \brief A class that provides common testing methods using GLUT.
//
/// This class provides common helper methods for testing VES on the desktop
/// using GLUT to manage the GL context, window, and mouse/keyboard.
#ifndef __vesTestHelper_h
#define __vesTestHelper_h

#include "vesGL.h"

#if defined(__APPLE__)
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include "vesRenderer.h"

#include <iostream>
#include <string>

class vesTestHelper
{
public:

  vesTestHelper();

  virtual ~vesTestHelper()
  {
  }

  virtual void handleKeyboard(unsigned char key, int x, int y)
  {
    vesNotUsed(x);
    vesNotUsed(y);

    if (key == 'q') {
      exit(0);
      //glutLeaveMainLoop();
    }
  }

  virtual void render()
  {
    if (mRenderer) {
      mRenderer->render();
      glutSwapBuffers();
    }
  }

  virtual void resize(int width, int height)
  {
    if (mRenderer) {
      mRenderer->resize(width, height, 1.0f);
    }
  }

  void setRenderer(vesRenderer::Ptr renderer)
  {
    mRenderer = renderer;
  }

  vesRenderer::Ptr renderer() const
  {
    return mRenderer;
  }

  virtual bool initTesting()
  {
    return true;
  }

  virtual bool doTesting()
  {
    return false;
  }

  virtual void init(int* argcp, char** argv, int windowWidth, int windowHeight, const std::string& windowTitle);

  virtual void startMainLoop();

  virtual void handleMouseClick(int button, int state, int x, int y);

  virtual void handleMouseMotion(int x, int y);

  virtual void handleLeftClickDown(int x, int y)
  {
  }

  virtual void handleLeftClickUp(int x, int y)
  {
  }

  virtual void handleRightClickUp(int x, int y)
  {
  }

  virtual void handleRightClickDown(int x, int y)
  {
  }


protected:

  vesRenderer::Ptr mRenderer;

  int mLastMousePositionX;
  int mLastMousePositionY;

  bool mIsLeftClick;
  bool mIsShiftKey;
};


namespace vesTestHelperGlobals {

vesTestHelper* testHelper;

void handleKeyboard(unsigned char key, int x, int y)
{
  testHelper->handleKeyboard(key, x, y);
}

void handleMouseClick(int button, int state, int x, int y)
{
  testHelper->handleMouseClick(button, state, x, y);
}

void handleMouseMotion(int x, int y)
{
  testHelper->handleMouseMotion(x, y);
}

void display(void)
{
  testHelper->render();
}

void reshape(int width, int height)
{
  testHelper->resize(width, height);
}

void idle(void)
{
  //glutPostRedisplay();
}

void timerCB(int millisec)
{
  glutTimerFunc(33, timerCB, 33);
  glutPostRedisplay();
}

}

vesTestHelper::vesTestHelper()
{
  if (vesTestHelperGlobals::testHelper) {
    std::cout << "Error: multiple instances of test helper detected." << std::endl;
  }
  vesTestHelperGlobals::testHelper = this;
  mLastMousePositionX = 0;
  mLastMousePositionY = 0;
  mIsLeftClick = false;
  mIsShiftKey = false;
}

void vesTestHelper::init(int* argcp, char** argv, int windowWidth, int windowHeight, const std::string& windowTitle)
{
  glutInit(argcp, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow(windowTitle.c_str());
  glutKeyboardFunc(vesTestHelperGlobals::handleKeyboard);
  glutMouseFunc(vesTestHelperGlobals::handleMouseClick);
  glutMotionFunc(vesTestHelperGlobals::handleMouseMotion);
  glutDisplayFunc(vesTestHelperGlobals::display);
  glutReshapeFunc(vesTestHelperGlobals::reshape);
  glutIdleFunc(vesTestHelperGlobals::idle);
}

void vesTestHelper::startMainLoop()
{
  glutTimerFunc(33, vesTestHelperGlobals::timerCB, 33);
  glutMainLoop();
}

void vesTestHelper::handleMouseClick(int button, int state, int x, int y)
{
  mIsLeftClick = false;
  mIsShiftKey = (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
  mLastMousePositionX = x;
  mLastMousePositionY = y;

  if (button == GLUT_LEFT_BUTTON) {
    mIsLeftClick = true;
    if (state == GLUT_DOWN) {
      this->handleLeftClickDown(x, y);
    }
    else if (state == GLUT_UP) {
      this->handleLeftClickUp(x, y);
    }
  }
  else if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN) {
      this->handleRightClickDown(x, y);
    }
    else if (state == GLUT_UP) {
      this->handleRightClickUp(x, y);
    }
  }
}

void vesTestHelper::handleMouseMotion(int x, int y)
{
  mLastMousePositionX = x;
  mLastMousePositionY = y;
}

#endif
